import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"
import lumieTcg
import "../Core/CardDescription.js" as Description

Rectangle {
    id: root

    width: parent ? parent.width : 1280
    height: parent ? parent.height : 720

    color: "#10151f"

    property var battleState: gameManager.snapshot || ({})
    property var players: battleState.players || []
    property int me: gameManager.playerIndex < 0 ? 0 : gameManager.playerIndex
    property var selfPlayer: players.length > me ? players[me] : ({
            characters: [],
            elementPoints: ({
                    current: 0
                })
        })
    property var enemyPlayer: players.length > 1 ? players[1 - me] : ({
            characters: [],
            handCardCount: 0
        })
    property var hand: battleState.self && battleState.self.handCardIds ? battleState.self.handCardIds : []
    property var cardAvailability: battleState.self && battleState.self.handAvailability ? battleState.self.handAvailability : []
    property var pendingTarget: ({})
    property string pendingTargetType: "None"
    property var selfCharacters: selfPlayer.characters || []
    property var enemyCharacters: enemyPlayer.characters || []
    property var skillAvailability: selfPlayer.skillAvailability || []
    property int activeIndex: selfPlayer.activeCharacterIndex === undefined ? 0 : selfPlayer.activeCharacterIndex
    property var activeCharacter: selfCharacters.length > activeIndex ? selfCharacters[activeIndex] : ({
            characterId: ""
        })
    property var skills: activeCharacter.characterId ? charDataBase.skillList(activeCharacter.characterId) : []

    property var displaySkills: skillAvailability
    property string weatherType: battleState.weather && battleState.weather.activeWeather ? battleState.weather.activeWeather.type : "None"
    property bool attacksDisabled: weatherType === "Sandstorm"
    property bool finished: false
    property bool actionPending: false
    property string resultText: ""
    property var replacement: battleState.pendingReplacement || null
    property bool choosingReplacement: replacement !== null && replacement.playerIndex === root.me
    property bool canChooseReplacement: choosingReplacement && !finished && !actionPending && networkClient.connected
    property bool canSwitch: canAct && (selfPlayer.switchesRemaining === undefined || selfPlayer.switchesRemaining > 0)
    property bool canAct: !replacement && !finished && !actionPending && networkClient.connected && battleState.stage === "Action" && gameManager.playerIndex >= 0 && battleState.currentPlayerIndex === root.me && !(selfPlayer.endedRound || false)
    property int gameSecondsLeft: selfPlayer.remainingTimeMs !== undefined ? Math.ceil(selfPlayer.remainingTimeMs / 1000) : 180
    property int pendingCard: -1
    property int pendingSkill: -1
    property string previewText: ""
    property string previewTitle: ""
    property string previewDescription: ""
    property int previewEp: 0
    property int previewHp: 0
    property int previewEnergy: 0
    property bool previewAffordable: true
    property string errorText: ""

    function pointCost(cost) {
        let total = 0;
        for (const key in cost) {
            if (key !== "ENERGY")
                total += Number(cost[key] || 0);
        }
        return total;
    }
    function cancelPreview() {
        pendingCard = -1;
        pendingSkill = -1;
        pendingTarget = ({});
        pendingTargetType = "None";
        previewText = "";
        previewTitle = "";
        previewDescription = "";
        previewEp = 0;
        previewHp = 0;
        previewEnergy = 0;
        previewAffordable = true;
    }
    function chooseTarget(playerIndex, zone, index) {
        if (pendingCard < 0 || !canAct)
            return;
        if (pendingTargetType === "OpponentSummon" && (playerIndex !== 1 - me || zone !== "Summon"))
            return;
        if (pendingTargetType === "Summon" && (playerIndex !== me || zone !== "Summon"))
            return;
        if ((pendingTargetType === "Character" || pendingTargetType === "CharacterPair") && (playerIndex !== me || zone !== "Character"))
            return;
        if (pendingTargetType === "CharacterPair" && pendingTarget.fromIndex === undefined) {
            pendingTarget = {
                playerIndex: playerIndex,
                zone: zone,
                fromIndex: index
            };
            previewText = "Source selected. Select the character who will receive the equipment.";
            return;
        }
        pendingTarget = {
            playerIndex: playerIndex,
            zone: zone,
            index: index,
            fromIndex: pendingTarget.fromIndex
        };
        previewText = "Target selected. Click the card again to confirm.";
    }
    function targetReady() {
        return pendingTargetType === "None" || pendingTarget.index !== undefined && (pendingTargetType !== "CharacterPair" || pendingTarget.fromIndex !== undefined && pendingTarget.fromIndex !== pendingTarget.index);
    }
    function formatTime(totalSeconds) {
        const seconds = Math.max(0, totalSeconds);
        const tail = seconds % 60;
        return Math.floor(seconds / 60) + ":" + (tail < 10 ? "0" : "") + tail;
    }
    function localSkill(skillName, fallbackIndex) {
        for (let i = 0; i < skills.length; ++i) {
            if (skills[i].name === skillName)
                return skills[i];
        }
        return ({});
    }
    function effectItems(player) {
        const stateItems = player && player.states ? player.states : [];
        const summonItems = player && player.summons ? player.summons : [];
        return stateItems.map(function (item) {
            return Object.assign({}, item, {
                kind: "state"
            });
        }).concat(summonItems.map(function (item, index) {
            return Object.assign({}, item, {
                kind: "summon",
                zoneIndex: index
            });
        }));
    }
    function unavailableReason(skill) {
        if (skill.unavailableReason)
            return skill.unavailableReason;
        if (skill.passive)
            return "Passive skill — activates automatically";
        if (root.activeCharacter.preparedSkill)
            return "Prepared skill: " + root.activeCharacter.preparedSkill;
        if (root.attacksDisabled)
            return "Sandstorm prevents attacks this round";
        if (!root.canAct)
            return selfPlayer.endedRound ? "Round already ended" : "Waiting for opponent";
        if (skill.remainingUses !== undefined && skill.remainingUses <= 0)
            return "Skill use limit reached for this round";
        if ((skill.energyCost || 0) > (root.activeCharacter.energy || 0))
            return "Not enough Energy";
        return "Not enough Element Points";
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.cancelPreview()
    }

    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#111827"
        }
        GradientStop {
            position: 0.5
            color: "#292334"
        }
        GradientStop {
            position: 1
            color: "#111016"
        }
    }

    Row {
        id: enemyHand
        z: 2
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        spacing: -24
        Repeater {
            model: Math.min(enemyPlayer.handCardCount || 0, 8)
            Rectangle {
                width: 66
                height: 92
                radius: 7
                color: "#26364d"
                border.color: "#c8a96a"
                border.width: 2
                Text {
                    anchors.centerIn: parent
                    text: "✦"
                    color: "#c8a96a"
                    font.pixelSize: 24
                }
            }
        }
    }

    // Persistent combat effects remain visible and update directly from snapshots.
    Rectangle {
        id: opponentEffects
        z: 3
        anchors.left: parent.left
        anchors.leftMargin: 88
        anchors.top: parent.top
        anchors.topMargin: 118
        width: 220
        height: Math.min(174, 34 + opponentEffectColumn.height)
        radius: 9
        color: "#80131b28"
        border.color: "#4e6077"
        clip: true
        Text {
            id: opponentEffectTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 8
            text: "Opponent effects"
            color: "#e5cf9a"
            font.bold: true
        }
        Flickable {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: opponentEffectTitle.bottom
            anchors.bottom: parent.bottom
            anchors.margins: 5
            contentHeight: opponentEffectColumn.height
            clip: true
            Column {
                id: opponentEffectColumn
                width: parent.width
                spacing: 5
                Repeater {
                    model: root.effectItems(root.enemyPlayer)
                    Rectangle {
                        required property var modelData
                        width: opponentEffectColumn.width
                        height: 44
                        radius: 6
                        color: "#b52a3548"
                        Image {
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            anchors.verticalCenter: parent.verticalCenter
                            width: 36
                            height: 36
                            source: assetsManager.resolveEffectImage(modelData.name, modelData.kind, modelData.icon || "")
                            fillMode: Image.PreserveAspectFit
                        }
                        Text {
                            anchors.fill: parent
                            anchors.margins: 7
                            anchors.leftMargin: 46
                            verticalAlignment: Text.AlignVCenter
                            text: modelData.name + (modelData.usage === null || modelData.usage === undefined ? "" : "  ×" + modelData.usage) + (modelData.characterIndex === null || modelData.characterIndex === undefined ? "" : " [" + (modelData.characterIndex + 1) + "]")
                            color: "white"
                            elide: Text.ElideRight
                        }
                        ToolTip.visible: effectMouse.containsMouse
                        ToolTip.text: modelData.description || modelData.name
                        MouseArea {
                            id: effectMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: root.pendingTargetType === "OpponentSummon" ? Qt.PointingHandCursor : Qt.ArrowCursor
                            onClicked: if (modelData.kind === "summon")
                                root.chooseTarget(1 - root.me, "Summon", modelData.zoneIndex)
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: ownEffects
        z: 3
        anchors.left: parent.left
        anchors.leftMargin: 88
        anchors.bottom: handPanel.top
        anchors.bottomMargin: 20
        width: 220
        height: Math.min(174, 34 + ownEffectColumn.height)
        radius: 9
        color: "#80131b28"
        border.color: "#4e6077"
        clip: true
        Text {
            id: ownEffectTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 8
            text: "Your states & summons"
            color: "#e5cf9a"
            font.bold: true
        }
        Flickable {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: ownEffectTitle.bottom
            anchors.bottom: parent.bottom
            anchors.margins: 5
            contentHeight: ownEffectColumn.height
            clip: true
            Column {
                id: ownEffectColumn
                width: parent.width
                spacing: 5
                Repeater {
                    model: root.effectItems(root.selfPlayer)
                    Rectangle {
                        required property var modelData
                        width: ownEffectColumn.width
                        height: 44
                        radius: 6
                        color: "#b5364559"
                        Image {
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            anchors.verticalCenter: parent.verticalCenter
                            width: 36
                            height: 36
                            source: assetsManager.resolveEffectImage(modelData.name, modelData.kind, modelData.icon || "")
                            fillMode: Image.PreserveAspectFit
                        }
                        Text {
                            anchors.fill: parent
                            anchors.margins: 7
                            anchors.leftMargin: 46
                            verticalAlignment: Text.AlignVCenter
                            text: modelData.name + (modelData.usage === null || modelData.usage === undefined ? "" : "  ×" + modelData.usage) + (modelData.characterIndex === null || modelData.characterIndex === undefined ? "" : " [" + (modelData.characterIndex + 1) + "]")
                            color: "white"
                            elide: Text.ElideRight
                        }
                        ToolTip.visible: ownEffectMouse.containsMouse
                        ToolTip.text: modelData.description || modelData.name
                        MouseArea {
                            id: ownEffectMouse
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: root.pendingTargetType === "Summon" ? Qt.PointingHandCursor : Qt.ArrowCursor
                            onClicked: if (modelData.kind === "summon")
                                root.chooseTarget(root.me, "Summon", modelData.zoneIndex)
                        }
                    }
                }
            }
        }
    }

    Text {
        z: 4
        visible: (root.previewHp !== 0) ? true : false
        anchors.horizontalCenter: enemyField.horizontalCenter
        anchors.top: enemyField.bottom
        anchors.topMargin: 4
        text: "Base damage HP " + root.previewHp
        color: "#b8ff8b8b"
        font.bold: true
        font.pixelSize: 16
        SequentialAnimation on opacity {
            running: (root.previewHp !== 0) ? true : false
            loops: Animation.Infinite
            NumberAnimation {
                to: 0.25
                duration: 430
            }
            NumberAnimation {
                to: 0.9
                duration: 430
            }
        }
    }

    Text {
        z: 2
        anchors.top: enemyHand.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Opponent hand  " + (enemyPlayer.handCardCount || 0)
        color: "#aab4c4"
        font.pixelSize: 12
    }

    // Enemy character field.
    Row {
        id: enemyField
        z: 2
        anchors.top: parent.top
        anchors.topMargin: 126
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 18
        Repeater {
            id: enemyCharacterRepeater
            model: root.enemyCharacters
            BattleCharacter {
                required property var modelData
                required property int index
                width: 132
                height: 150
                character: modelData
                profile: charDataBase.details(modelData.characterId)
                active: index === enemyPlayer.activeCharacterIndex
                opponent: true
            }
        }
    }

    WeatherBanner {
        z: 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        width: 250
        weatherName: root.weatherType
        description: "Round " + (battleState.round || 1) + " • " + ({
                Rain: "Hydro applied to all characters",
                Snow: "Cryo applied to all characters",
                Thunderstorm: "Electro and 1 damage to a random character",
                Sandstorm: "Skills disabled this round",
                Cataclysm: "Element applications cleared",
                BurningField: "Summons cleared; random Pyro application",
                Tornado: "Hands shuffled into deck; draw 3",
                None: "Clear weather"
            }[root.weatherType] || root.weatherType)
        remainingRounds: battleState.weather && battleState.weather.activeWeather ? battleState.weather.activeWeather.remainingRounds : 0
    }

    CountdownClock {
        z: 4
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 24
        deadlineEpochMs: battleState.actionDeadlineEpochMs || 0
        visible: !root.finished && battleState.currentPlayerIndex === root.me && (!(selfPlayer.endedRound || false) || root.choosingReplacement)
    }
    Rectangle {
        z: 4
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 72
        anchors.rightMargin: 24
        width: 108
        height: 32
        radius: 16
        color: "#b51d2838"
        border.color: "#65768c"
        Text {
            anchors.centerIn: parent
            text: "Game  " + root.formatTime(root.gameSecondsLeft)
            color: "#dce7f5"
            font.bold: true
        }
    }
    Timer {
        interval: 1000
        repeat: true
        running: !root.finished && battleState.currentPlayerIndex === root.me && (!selfPlayer.endedRound || root.choosingReplacement) && root.gameSecondsLeft > 0
        onTriggered: root.gameSecondsLeft--
    }

    // Element points are deliberately vertical and use the omni asset.
    Column {
        z: 2
        anchors.left: parent.left
        anchors.leftMargin: 28
        anchors.verticalCenter: parent.verticalCenter
        spacing: 3
        Text {
            text: "EP"
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Repeater {
            model: selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0
            Image {
                width: 29
                height: 29
                source: "qrc:/lumieTcg/assets/elements/omni.png"
                fillMode: Image.PreserveAspectFit
            }
        }
        Text {
            visible: (root.previewEp !== 0) ? true : false
            text: root.previewEp + " EP"
            color: "#a8d9f3ff"
            font.bold: true
            SequentialAnimation on opacity {
                running: (root.previewEp !== 0) ? true : false
                loops: Animation.Infinite
                NumberAnimation {
                    to: 0.25
                    duration: 430
                }
                NumberAnimation {
                    to: 1
                    duration: 430
                }
            }
        }
    }

    // Our character field. A second click on the same character confirms the switch.
    Row {
        id: ownField
        z: 2
        anchors.bottom: handPanel.top
        anchors.bottomMargin: 14
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        Repeater {
            id: ownCharacterRepeater
            model: root.selfCharacters
            BattleCharacter {
                required property var modelData
                required property int index
                character: modelData
                profile: charDataBase.details(modelData.characterId)
                active: index === root.activeIndex
                selectable: root.pendingCard < 0 && index !== root.activeIndex && (root.canSwitch || root.canChooseReplacement)
                targetSelectable: root.pendingCard >= 0 && root.canAct && (root.pendingTargetType === "Character" || root.pendingTargetType === "CharacterPair")
                targetSelected: root.pendingCard >= 0 && root.pendingTarget.zone === "Character" && (root.pendingTarget.index === index || root.pendingTarget.fromIndex === index)
                onTargetRequested: root.chooseTarget(root.me, "Character", index)
                onSwitchRequested: {
                    root.errorText = "";
                    root.actionPending = true;
                    root.cancelPreview();
                    if (root.choosingReplacement)
                        gameManager.chooseActiveCharacter(index);
                    else
                        gameManager.switchCharacter(index);
                }
            }
        }
    }

    Text {
        z: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: ownField.top
        anchors.bottomMargin: 12
        width: 540
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        visible: root.replacement !== null
        text: root.choosingReplacement ? "Your active character was defeated. Double-click a living character to continue. This does not use your round switch." : "Waiting for opponent to choose a replacement. Your turn will resume afterward."
        color: "#f4d27a"
        font.pixelSize: 15
    }

    // Skills: click once for a gray preview, click the same skill again to confirm.
    Column {
        z: 2
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.verticalCenter: parent.verticalCenter
        width: 235
        spacing: 8
        Text {
            text: "Skills — " + root.activeCharacter.characterId
            color: "white"
            font.bold: true
            font.pixelSize: 16
        }
        Repeater {
            model: root.displaySkills
            Rectangle {
                required property var modelData
                required property int index
                property var detail: root.localSkill(modelData.name || "", index)
                property int epCost: modelData.elementPointCost === undefined ? (detail.cost || 0) : modelData.elementPointCost
                property int energyCost: modelData.energyCost || 0
                width: 235
                height: 58
                radius: 9
                property bool usable: !root.attacksDisabled && modelData.available === true
                opacity: usable && root.canAct ? 1.0 : 0.38
                color: root.pendingSkill === index ? "#69717c" : "#273448"
                border.color: usable ? "#78d9b0" : "#666b73"
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    anchors.verticalCenter: parent.verticalCenter
                    width: 130
                    text: modelData.name || detail.name
                    color: "white"
                    elide: Text.ElideRight
                }
                Text {
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    text: epCost + " EP" + (energyCost > 0 ? " / " + energyCost + " EN" : "") + "\n" + (modelData.remainingUses === undefined ? "" : modelData.remainingUses + "/" + modelData.maxUse + " uses")
                    color: "#c8e7ff"
                    horizontalAlignment: Text.AlignRight
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.pendingSkill === index) {
                            if (root.canAct && parent.usable) {
                                root.errorText = "";
                                root.actionPending = true;
                                gameManager.useSkill(index, parent.epCost, {
                                    playerIndex: 1 - root.me,
                                    zone: "Character",
                                    index: enemyPlayer.activeCharacterIndex
                                });
                            }
                            root.cancelPreview();
                        } else {
                            root.pendingCard = -1;
                            root.pendingSkill = index;
                            root.previewText = parent.usable && root.canAct ? (modelData.name + " will cost " + parent.epCost + " EP. Click again to confirm.") : root.unavailableReason(modelData);
                            root.previewTitle = modelData.name || parent.detail.name;
                            const profile = charDataBase.details(root.activeCharacter.characterId);
                            root.previewDescription = Description.describe((profile.skills || {})[modelData.name] || parent.detail);
                            root.previewAffordable = parent.usable && root.canAct;
                            root.previewEp = -parent.epCost;
                            root.previewHp = parent.detail.hpDelta || 0; // Base damage; reactions may change the result.
                            root.previewEnergy = parent.energyCost > 0 ? -parent.energyCost : Math.min(1, (root.activeCharacter.maxEnergy || 3) - (root.activeCharacter.energy || 0));
                        }
                    }
                }
            }
        }
        GameButton {
            width: 235
            height: 48
            text: root.replacement ? "Choose replacement first" : root.actionPending ? "Sending…" : selfPlayer.endedRound ? "Round ended" : !root.canAct ? "Waiting for opponent" : "End Round"
            enabled: root.canAct
            onClicked: {
                root.cancelPreview();
                root.errorText = "";
                root.actionPending = true;
                gameManager.endRound();
            }
        }
    }

    Rectangle {
        z: 3
        visible: root.previewText.length > 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: Math.min(560, parent.width - 40)
        height: 68
        radius: 9
        color: "#d05f6670"
        Text {
            id: previewLabel
            anchors.centerIn: parent
            width: parent.width - 24
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            text: root.previewText
            color: "white"
            font.pixelSize: 14
        }
    }

    ActionPreviewPanel {
        z: 4
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 12
        width: 260
        title: root.previewTitle
        description: root.previewDescription
        epDelta: root.previewEp
        hpDelta: root.previewHp
        energyDelta: root.previewEnergy
        affordable: root.previewAffordable
        SequentialAnimation on opacity {
            running: root.previewTitle.length > 0
            loops: Animation.Infinite
            NumberAnimation {
                to: 0.68
                duration: 520
            }
            NumberAnimation {
                to: 1
                duration: 520
            }
        }
    }

    // Our hand supports click/confirm and horizontal hold-drag for hands over eight cards.
    Rectangle {
        id: handPanel
        z: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 320
        anchors.rightMargin: 285
        anchors.bottomMargin: 12
        height: 158
        radius: 14
        color: "#b3151c28"
        border.color: "#59677a"
        Flickable {
            anchors.fill: parent
            anchors.margins: 8
            contentWidth: Math.max(width, handRow.width)
            contentHeight: height
            flickableDirection: Flickable.HorizontalFlick
            clip: true
            Row {
                id: handRow
                spacing: 8
                height: parent.height
                Repeater {
                    model: root.hand
                    Rectangle {
                        required property string modelData

                        required property int index
                        property var cardDetail: cardDataBase.details(modelData)
                        property var serverInfo: root.cardAvailability[index] || ({})
                        property int cardCost: serverInfo.elementPointCost === undefined ? root.pointCost(cardDetail.cost || {}) : serverInfo.elementPointCost
                        property int energyCost: serverInfo.energyCost === undefined ? Number((cardDetail.cost || {}).ENERGY || 0) : serverInfo.energyCost
                        property bool cardUsable: root.canAct && energyCost <= (root.activeCharacter.energy || 0) && cardCost <= (selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0)
                        width: 92
                        height: 136
                        radius: 8
                        opacity: cardUsable ? 1.0 : 0.4
                        color: root.pendingCard === index ? "#737983" : "#263247"
                        border.width: root.pendingCard === index ? 3 : 1
                        border.color: "#d7bd80"
                        Image {
                            anchors.fill: parent
                            anchors.margins: 4
                            source: assetsManager.resolveCardImage(modelData)
                            fillMode: Image.PreserveAspectCrop
                        }
                        Rectangle {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            height: 30
                            color: "#c0000000"
                        }
                        Text {
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: 58
                            width: parent.width - 8
                            text: modelData
                            color: "white"
                            font.pixelSize: 10
                            elide: Text.ElideRight
                            horizontalAlignment: Text.AlignHCenter
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                const cost = parent.cardCost;
                                if (root.pendingCard === index) {
                                    if (!root.targetReady()) {
                                        root.previewText = "Select a valid target before confirming this card.";
                                        return;
                                    }
                                    if (parent.cardUsable) {
                                        root.errorText = "";
                                        root.actionPending = true;
                                        gameManager.playCard(index, cost, root.pendingTarget);
                                    }
                                    root.cancelPreview();
                                } else {
                                    root.pendingSkill = -1;
                                    root.pendingCard = index;
                                    root.pendingTargetType = parent.serverInfo.targetType || "None";
                                    root.pendingTarget = root.pendingTargetType === "Character" ? {
                                        playerIndex: root.me,
                                        zone: "Character",
                                        index: root.activeIndex
                                    } : ({});
                                    root.previewText = parent.cardUsable ? modelData + " will cost " + cost + " EP. Click again to confirm." : (!root.canAct ? "Waiting for opponent" : (parent.energyCost > (root.activeCharacter.energy || 0) ? "Not enough Energy" : "Not enough Element Points"));
                                    const detail = cardDataBase.details(modelData);
                                    root.previewTitle = detail.name || modelData;
                                    root.previewDescription = Description.describe(detail);
                                    if (root.pendingTargetType !== "None")
                                        root.previewText = root.pendingTargetType === "CharacterPair" ? "Select the character with equipment, then its recipient." : root.pendingTargetType === "Character" ? "Active character selected. Click another character to change target, or click card to confirm." : "Select a " + (root.pendingTargetType === "OpponentSummon" ? "opponent" : "friendly") + " summon, then click card to confirm.";
                                    root.previewAffordable = parent.cardUsable;
                                    root.previewEp = -cost;
                                    root.previewHp = 0;
                                    root.previewEnergy = -parent.energyCost;
                                }
                            }
                        }
                    }
                }
            }
            ScrollBar.horizontal: ScrollBar {
                policy: root.hand.length > 8 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            }
        }
    }

    Text {
        z: 3
        anchors.left: handPanel.left
        anchors.bottom: handPanel.top
        text: "Hand " + root.hand.length + " • Deck " + (selfPlayer.deckCardCount || 0) + " • Switches left: " + (selfPlayer.switchesRemaining === undefined ? 1 : selfPlayer.switchesRemaining)
        color: "#cbd5e1"
        font.pixelSize: 13
    }

    Connections {
        target: gameManager
        function onSnapshotChanged() {
            root.actionPending = false;
            root.cancelPreview();
            root.gameSecondsLeft = selfPlayer.remainingTimeMs !== undefined ? Math.ceil(selfPlayer.remainingTimeMs / 1000) : 180;
        }
        function onGameError(message) {
            root.actionPending = false;
            root.errorText = message;
        }
        function onGameEnded(reason) {
            root.finished = true;
            root.resultText = reason;
            root.cancelPreview();
        }
        function onGameEventsReceived(events) {
            for (let i = 0; i < events.length; ++i) {
                const event = events[i];
                if (event.eventType === "GameEnded" && event.winnerIndex !== undefined)
                    root.resultText = (event.winnerIndex === root.me ? "Victory — " : "Defeat — ") + event.reason;
                if (event.eventType !== "SkillUsed")
                    continue;
                const player = root.players[event.playerIndex];
                if (!player)
                    continue;
                const characterIndex = event.characterIndex === undefined ? (player.activeCharacterIndex || 0) : event.characterIndex;
                const character = player.characters[characterIndex];
                if (!character)
                    continue;
                const profile = charDataBase.details(character.characterId);
                const item = event.playerIndex === root.me ? ownCharacterRepeater.itemAt(characterIndex) : enemyCharacterRepeater.itemAt(characterIndex);
                if (item)
                    item.playSkill(profile.element_type || "Physical");
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        z: 20
        visible: root.finished
        color: "#dd10151f"
        MouseArea {
            anchors.fill: parent
        }
        Column {
            anchors.centerIn: parent
            spacing: 24
            Text {
                text: "Match ended"
                color: "white"
                font.pixelSize: 28
            }
            Text {
                text: root.resultText
                color: "#e5cf9a"
                font.pixelSize: 18
            }
            GameButton {
                text: "Main menu"
                onClicked: stack.replace("./MainMenu.qml")
            }
        }
    }

    Text {
        z: 4
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 12
        text: !networkClient.connected && !root.finished ? "Disconnected from server" : root.errorText
        color: "#ff7777"
        font.bold: true
    }
}
