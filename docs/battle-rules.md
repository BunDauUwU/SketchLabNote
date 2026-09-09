# Battle rules and editable data

## Skill limits

Each skill in `server/character.json` has `maxUse: 1`. Set it to a non-negative integer:

- `0`: unavailable.
- `1`: once per round.
- `2`, `3`, etc.: that many uses per round.

The server counts uses separately for every skill on every character. Switching does not reset them. A new round resets all usage counters. Bursts use the same rule, and still require Energy. Talent-triggered skills count toward the limit; their cost is included in the talent card's cost. Passive skills activate automatically rather than through a skill button.

The Qt client embeds `json/character.json` for descriptions. Keep its `maxUse` values aligned with the server copy, restart the server after editing server JSON, and rebuild the client after editing embedded JSON. The server's snapshot controls actual availability and prices.

Kokomi's server key is `Sangonomiya Kokomi`. Client character definitions, including Sumeru, are under `standard` so the existing CharacterDatabase can read them.

## Switching and defeat

A player can voluntarily switch once per round. The limit also applies to a card that voluntarily changes their active character. A normal switch passes control unless a fast-switch effect applies or the opponent has ended their round.

If an active character reaches zero HP after an action, `pendingReplacement` contains `playerIndex` and `resumePlayerIndex`. Only that player's replacement command or concession is accepted during this phase, including when that player has already ended their round. Select a living character by double-clicking it. This replacement does not spend the normal switch allowance. The suspended player's EP, hand, skill counters, round-ended status and remaining game time are preserved. If no characters remain alive, the match ends immediately.

## Effects

`server/effectEngine.js` interprets the `modify` and `effect` records used by the character, card, state and summon databases. It keeps runtime modifiers separate from source JSON and tracks usage, per-round allowances, duration, counters, equipment, preparation and character/team ownership.

The engine dispatches cost, skill, attack, defense, reaction, switching, creation/removal, invocation and round-start/end triggers. Summons activate their JSON effects and spend usage; exhausted effects are removed. End-of-round damage can end a match before the next round begins. Damage, healing, shields, infusion, resource changes, card draw, equipment movement and talent modifications run on the server. Invalid card/skill actions are resolved on a trial copy and do not partially spend resources or consume cards.

The custom game uses a single Omni EP pool. `APPEND_DICE` adds EP and cost reductions change EP cost. `FIXED_DICE` and `REROLL` cannot change an already-Omni pool, so they do not generate extra EP.

## Client controls and images

- Click a skill/card to preview; click it again to confirm.
- Character-targeting cards default to your active character. Click another living character to change the target.
- For Quick Knit or Send Off, click the appropriate summon before confirming.
- For equipment transfer, click the source character, then the recipient, then confirm the card.
- Switches and skill uses remaining are displayed from snapshots.
- Element applications use `assets/elements`; summons use `assets/summons`; states use `assets/states`.
- Image lookup normalizes spaces, punctuation and case. States use their JSON `icon` when there is no named image; effects without a dedicated image use the generic state icon.
- DeckScreen's three buttons select the independently saved deck slots. Hover details are generated from JSON costs, effects, conditions and requirements, rather than database indices or raw JSON dumps.

## Verification

Run `npm test --prefix server` for the rule, effect, description and WebSocket protocol tests. Qt smoke checks during development also render both screens, resolve representative images, select a summon target, and verify that deck1/2/3 save and reload independently using a temporary SQLite database.
