// Shared, deterministic presentation of the JSON rules. No database index assumptions.
function list(value) {
    return value && typeof value !== "string" && typeof value.length === "number"
        ? Array.prototype.slice.call(value) : value ? [value] : [];
}

function label(value) {
    const names = {PHYSICAL: "Physical", PIERCE: "Piercing", ENERGY: "Energy", ANY: "any element", SAME: "matching element",
        ACTIVE: "your active character", SELF: "this character", ALL: "all your characters", OPPOSE: "the opponent", TEAM: "your team",
        PLAYER: "you", SKILL: "this skill", NORMAL_ATTACK: "using a Normal Attack", ELEMENTAL_SKILL: "using an Elemental Skill",
        ELEMENTAL_BURST: "using an Elemental Burst", IS_ACTIVE: "this character is active"};
    if (value === undefined || value === null) return "";
    if (names[value]) return names[value];
    return String(value).replace(/\{?__select\}?/g, "the selected character").replace(/_/g, " ");
}

function values(value) {
    if (Array.isArray(value)) return value.map(values).join(", ");
    if (value && typeof value === "object") {
        return Object.keys(value).map(function (key) { return label(key) + ": " + values(value[key]); }).join(", ");
    }
    return label(value);
}

function pointCost(cost) {
    let total = 0;
    for (const key in (cost || {})) if (key !== "ENERGY") total += Number(cost[key] || 0);
    return total;
}

function conditionText(condition) {
    if (typeof condition === "string") return label(condition);
    if (!condition || typeof condition !== "object") return "";
    const operators = {equal: "is", unequal: "is not", large: "is greater than", small: "is less than", less: "is less than"};
    if (condition.logic === "is_active") return label(condition.who) + " is active";
    if (condition.logic === "check")
        return [label(condition.whose), label(condition.what), operators[condition.operator] || label(condition.operator), values(condition.condition)].filter(Boolean).join(" ");
    if (condition.logic === "have") return [label(condition.where || condition.whose), "has", values(condition.condition || condition.what)].filter(Boolean).join(" ");
    return values(condition);
}

function modifierText(mod) {
    const effect = mod.effect || {};
    const type = effect.effect_type || "";
    const value = effect.effect_value;
    const amount = values(value);
    let text = "";
    if (type === "HEAL") text = "Restore " + amount + " HP";
    else if (type === "DRAW_CARD") text = "Draw " + amount + " card(s)";
    else if (type === "CHANGE_ENERGY" || type === "SKILL_ADD_ENERGY") text = "Change Energy by " + amount;
    else if (type === "APPLICATION") text = "Apply " + amount;
    else if (type === "INFUSION") text = "Infuse attacks with " + amount;
    else if (type === "ADD_STATE") text = "Apply status: " + amount;
    else if (type === "SHIELD") text = "Create shield: " + values(value && value.shield !== undefined ? value.shield : value);
    else if (type === "HURT") text = "Change incoming damage by " + amount;
    else if (type === "DMG") text = "Change damage by " + amount;
    else if (type.endsWith("_DMG")) text = "Deal " + amount + " " + label(type.slice(0, -4)) + " damage";
    else if (type.indexOf("COST_") === 0) text = "Change " + label(type.slice(5)) + " cost by " + amount;
    else if (type === "CHANGE_COST") text = "Change cost: " + amount;
    else if (type === "CHANGE_SUMMON_USAGE") text = "Change summon uses by " + amount;
    else if (type === "CHANGE_STATE_USAGE") text = "Change status uses by " + amount;
    else if (type === "CHANGE_CHARACTER") text = "Switch character: " + amount;
    else if (type === "APPEND_DICE") text = "Gain resources: " + amount;
    else if (type) text = label(type) + (amount ? ": " + amount : "");
    else if (Object.keys(effect).length) text = values(effect);
    if (!text) return "";
    if (mod.effect_obj) text += " (" + label(mod.effect_obj) + ")";
    const triggers = {end: "At round end", start: "At round start", play_card: "When played", use_skill: "When using a skill",
        after_attack: "After an attack", defense: "When taking damage", after_change: "After switching character", change: "When switching character"};
    if (mod.trigger_time) text = (triggers[mod.trigger_time] || "On " + label(mod.trigger_time)) + ": " + text;
    const conditions = list(mod.condition).map(conditionText).filter(Boolean);
    if (conditions.length) text += "; if " + conditions.join(" and ");
    const limits = mod.time_limit || {};
    if (limits.DURATION !== undefined) text += "; lasts " + limits.DURATION + " round(s)";
    if (limits.USAGE !== undefined) text += "; " + limits.USAGE + " use(s)";
    return text + ".";
}

function describe(definition) {
    const d = definition || {};
    const lines = [];
    if (d.tag && list(d.tag).length) lines.push(list(d.tag).join(" · "));
    if (d.type) lines.push(list(d.type).join(" · "));
    if (d.cost) lines.push("Cost: " + pointCost(d.cost) + " EP" + (d.cost.ENERGY ? " + " + d.cost.ENERGY + " Energy" : "") + ".");
    if (d.maxUse !== undefined) lines.push("Limit: " + d.maxUse + " use(s) per round.");
    for (const element in (d.damage || {})) lines.push("Deal " + d.damage[element] + " " + label(element) + " damage.");
    for (const name in (d.summon || {})) lines.push("Summon " + name + " ×" + d.summon[name] + ".");
    for (const name in (d.create || {})) lines.push("Create " + name + " ×" + d.create[name] + ".");
    if (d.energy) lines.push("Gain " + d.energy + " Energy.");
    if (d.use_skill) lines.push("Use skill: " + d.use_skill + ".");
    for (const key in (d.deck_limit || {})) {
        lines.push(key === "character" ? "Required character: " + d.deck_limit[key] + "." : "Deck requirement: " + label(key) + " ×" + d.deck_limit[key] + ".");
    }
    const requirements = list(d.combat_limit).map(conditionText).filter(Boolean);
    if (requirements.length) lines.push("Play requirement: " + requirements.join("; ") + ".");
    const modifiers = list(d.modify).map(modifierText).filter(Boolean);
    for (const text of modifiers) if (lines.indexOf(text) < 0) lines.push(text);
    if (!lines.length) lines.push(d.description || "No effect description is available for this entry.");
    return lines.join("\n\n");
}

function describeCharacter(definition) {
    const d = definition || {};
    const lines = [label(d.element_type) + (d.weapon ? " · " + label(d.weapon) : "")];
    for (const name in (d.skills || {})) lines.push(name + "\n" + describe(d.skills[name]));
    return lines.filter(Boolean).join("\n\n");
}
