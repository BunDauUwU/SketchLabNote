import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"
import lumieTcg

Rectangle {
    id: root

    width: parent ? parent.width : 1280
    height: parent ? parent.height : 720

    color: "#10151f"

    property var state: gameManager.snapshot || ({})
    property var players: state.players || []
    property int me: gameManager.playerIndex < 0 ? 0 : gameManager.playerIndex
    property var selfPlayer: players.length > me ? players[me] : ({ characters: [], elementPoints: ({ current: 0 }) })
    property var enemyPlayer: players.length > 1 ? players[1 - me] : ({ characters: [], handCardCount: 0 })
    property var hand: state.self && state.self.handCardIds ? state.self.handCardIds : []
    property var selfCharacters: selfPlayer.characters || []
    property var enemyCharacters: enemyPlayer.characters || []
    property int activeIndex: selfPlayer.activeCharacterIndex === undefined ? 0 : selfPlayer.activeCharacterIndex
    property var activeCharacter: selfCharacters.length > activeIndex ? selfCharacters[activeIndex] : ({ characterId: "" })
    property var skills: activeCharacter.characterId ? charDataBase.skillList(activeCharacter.characterId) : []
    property bool canAct: state.currentPlayerIndex === root.me && !(selfPlayer.endedRound || false)
    property int gameSecondsLeft: selfPlayer.remainingTimeMs ? Math.ceil(selfPlayer.remainingTimeMs / 1000) : 180
    property int pendingCard: -1
    property int pendingSkill: -1
    property string previewText: ""
    property string previewTitle: ""
    property string previewDescription: ""
    property int previewEp: 0
    property int previewHp: 0
    property int previewEnergy: 0
    property string errorText: ""

    function cancelPreview() {
        pendingCard = -1
        pendingSkill = -1
        previewText = ""
        previewTitle = ""
        previewDescription = ""
        previewEp = 0; previewHp = 0; previewEnergy = 0
    }
    function formatTime(totalSeconds) {
        const seconds = Math.max(0, totalSeconds)
        const tail = seconds % 60
        return Math.floor(seconds / 60) + ":" + (tail < 10 ? "0" : "") + tail
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.cancelPreview()
    }

    gradient: Gradient {
        GradientStop { position: 0; color: "#111827" }
        GradientStop { position: 0.5; color: "#292334" }
        GradientStop { position: 1; color: "#111016" }
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
                width: 66; height: 92; radius: 7
                color: "#26364d"; border.color: "#c8a96a"; border.width: 2
                Text { anchors.centerIn: parent; text: "✦"; color: "#c8a96a"; font.pixelSize: 24 }
            }
        }
    }

    Text {
        z: 4; visible: root.previewHp !== 0
        anchors.horizontalCenter: enemyField.horizontalCenter; anchors.top: enemyField.bottom; anchors.topMargin: 4
        text: "Preview HP " + root.previewHp
        color: "#b8ff8b8b"; font.bold: true; font.pixelSize: 16
        SequentialAnimation on opacity {
            running: parent.visible; loops: Animation.Infinite
            NumberAnimation { to: 0.25; duration: 430 }
            NumberAnimation { to: 0.9; duration: 430 }
        }
    }

    Text {
        z: 2; anchors.top: enemyHand.bottom; anchors.horizontalCenter: parent.horizontalCenter
        text: "Opponent hand  " + (enemyPlayer.handCardCount || 0); color: "#aab4c4"; font.pixelSize: 12
    }

    // Enemy character field.
    Row {
        id: enemyField
        z: 2
        anchors.top: parent.top; anchors.topMargin: 126
        anchors.horizontalCenter: parent.horizontalCenter; spacing: 18
        Repeater {
            id: enemyCharacterRepeater
            model: root.enemyCharacters
            BattleCharacter {
                required property var modelData
                required property int index
                width: 132; height: 150
                character: modelData
                profile: charDataBase.details(modelData.characterId)
                active: index === enemyPlayer.activeCharacterIndex
                opponent: true
            }
        }
    }

    WeatherBanner {
        z: 2; anchors.left: parent.left; anchors.top: parent.top; anchors.margins: 20
        width: 250
        weatherName: state.weather && state.weather.activeWeather ? state.weather.activeWeather.type : "None"
        description: "Round " + (state.round || 1)
        remainingRounds: 1
    }

    CountdownClock {
        z: 4; anchors.top: parent.top; anchors.right: parent.right; anchors.margins: 24
        deadlineEpochMs: state.actionDeadlineEpochMs || 0
        visible: state.currentPlayerIndex === root.me && !(selfPlayer.endedRound || false)
    }
    Rectangle {
        z: 4; anchors.top: parent.top; anchors.right: parent.right; anchors.topMargin: 72; anchors.rightMargin: 24
        width: 108; height: 32; radius: 16; color: "#b51d2838"; border.color: "#65768c"
        Text { anchors.centerIn: parent; text: "Game  " + root.formatTime(root.gameSecondsLeft); color: "#dce7f5"; font.bold: true }
    }
    Timer { interval: 1000; repeat: true; running: root.canAct && root.gameSecondsLeft > 0; onTriggered: root.gameSecondsLeft-- }

    // Element points are deliberately vertical and use the omni asset.
    Column {
        z: 2; anchors.left: parent.left; anchors.leftMargin: 28; anchors.verticalCenter: parent.verticalCenter
        spacing: 3
        Text { text: "EP"; color: "white"; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
        Repeater {
            model: selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0
            Image { width: 29; height: 29; source: "qrc:/assets/elements/omni.png"; fillMode: Image.PreserveAspectFit }
        }
        Text {
            visible: root.previewEp !== 0
            text: root.previewEp + " EP"; color: "#a8d9f3ff"; font.bold: true
            SequentialAnimation on opacity {
                running: parent.visible; loops: Animation.Infinite
                NumberAnimation { to: 0.25; duration: 430 }
                NumberAnimation { to: 1; duration: 430 }
            }
        }
    }

    // Our character field. A second click on the same character confirms the switch.
    Row {
        id: ownField
        z: 2; anchors.bottom: handPanel.top; anchors.bottomMargin: 14
        anchors.horizontalCenter: parent.horizontalCenter; spacing: 20
        Repeater {
            id: ownCharacterRepeater
            model: root.selfCharacters
            BattleCharacter {
                required property var modelData
                required property int index
                character: modelData
                profile: charDataBase.details(modelData.characterId)
                active: index === root.activeIndex
                selectable: index !== root.activeIndex && state.currentPlayerIndex === root.me && !(selfPlayer.endedRound || false)
                onSwitchRequested: gameManager.switchCharacter(index)
            }
        }
    }

    // Skills: click once for a gray preview, click the same skill again to confirm.
    Column {
        z: 2; anchors.right: parent.right; anchors.rightMargin: 24; anchors.verticalCenter: parent.verticalCenter
        width: 235; spacing: 8
        Text { text: "Skills — " + root.activeCharacter.characterId; color: "white"; font.bold: true; font.pixelSize: 16 }
        Repeater {
            model: root.skills
            Rectangle {
                required property var modelData
                required property int index
                width: 235; height: 58; radius: 9
                color: root.pendingSkill === index ? "#69717c" : "#273448"
                border.color: modelData.cost <= (selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0) ? "#78d9b0" : "#d76b6b"
                Text { anchors.left: parent.left; anchors.leftMargin: 12; anchors.verticalCenter: parent.verticalCenter; width: 170; text: modelData.name; color: "white"; elide: Text.ElideRight }
                Text { anchors.right: parent.right; anchors.rightMargin: 10; anchors.verticalCenter: parent.verticalCenter; text: modelData.cost + " EP"; color: "#c8e7ff" }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.pendingSkill === index) {
                            if (root.canAct && modelData.cost <= selfPlayer.elementPoints.current)
                                gameManager.useSkill(index, modelData.cost, { playerIndex: 1 - root.me, zone: "Character", index: enemyPlayer.activeCharacterIndex })
                            root.cancelPreview()
                        } else {
                            root.pendingCard = -1; root.pendingSkill = index
                            root.previewText = modelData.name + " will cost " + modelData.cost + " EP. Click again to confirm."
                            root.previewTitle = modelData.name
                            root.previewDescription = modelData.description || "Character skill"
                            root.previewEp = -modelData.cost
                            root.previewHp = modelData.hpDelta || 0
                            root.previewEnergy = modelData.energyDelta || 0
                        }
                    }
                }
            }
        }
        GameButton {
            width: 235; height: 48
            text: selfPlayer.endedRound ? "Waiting for opponent" : "End Round"
            enabled: root.canAct
            onClicked: { root.cancelPreview(); gameManager.endRound() }
        }
    }

    Rectangle {
        z: 3; visible: root.previewText.length > 0
        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
        width: Math.min(560, previewLabel.implicitWidth + 36); height: 48; radius: 9; color: "#d05f6670"
        Text { id: previewLabel; anchors.centerIn: parent; text: root.previewText; color: "white"; font.pixelSize: 14 }
    }

    ActionPreviewPanel {
        z: 4; anchors.left: parent.left; anchors.bottom: handPanel.top
        anchors.leftMargin: 24; anchors.bottomMargin: 18
        title: root.previewTitle
        description: root.previewDescription
        epDelta: root.previewEp; hpDelta: root.previewHp; energyDelta: root.previewEnergy
        affordable: root.canAct && -root.previewEp <= (selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0)
        SequentialAnimation on opacity {
            running: root.previewTitle.length > 0; loops: Animation.Infinite
            NumberAnimation { to: 0.68; duration: 520 }
            NumberAnimation { to: 1; duration: 520 }
        }
    }

    // Our hand supports click/confirm and horizontal hold-drag for hands over eight cards.
    Rectangle {
        id: handPanel
        z: 2; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
        anchors.leftMargin: 105; anchors.rightMargin: 285; anchors.bottomMargin: 12
        height: 174; radius: 14; color: "#b3151c28"; border.color: "#59677a"
        Flickable {
            anchors.fill: parent; anchors.margins: 8
            contentWidth: Math.max(width, handRow.width); contentHeight: height
            flickableDirection: Flickable.HorizontalFlick; clip: true
            Row {
                id: handRow; spacing: 8; height: parent.height
                Repeater {
                    model: root.hand
                    Rectangle {
                        required property string modelData

                        required property int index
                        width: 102; height: 150; radius: 8
                        color: root.pendingCard === index ? "#737983" : "#263247"
                        border.width: root.pendingCard === index ? 3 : 1; border.color: "#d7bd80"
                        Image { anchors.fill: parent; anchors.margins: 4; source: assetsManager.resolveCardImage(modelData); fillMode: Image.PreserveAspectCrop }
                        Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 30; color: "#c0000000" }
                        Text { anchors.centerIn: parent; anchors.verticalCenterOffset: 58; width: parent.width - 8; text: modelData; color: "white"; font.pixelSize: 10; elide: Text.ElideRight; horizontalAlignment: Text.AlignHCenter }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                const cost = cardDataBase.cost(modelData)
                                if (root.pendingCard === index) {
                                    if (root.canAct && cost <= selfPlayer.elementPoints.current)
                                        gameManager.playCard(index, cost, {})
                                    root.cancelPreview()
                                } else {
                                    root.pendingSkill = -1; root.pendingCard = index
                                    root.previewText = modelData + " will cost " + cost + " EP. Click again to confirm."
                                    const detail = cardDataBase.details(modelData)
                                    root.previewTitle = detail.name || modelData
                                    root.previewDescription = "Card effect • " + (detail.tag || "Action")
                                    root.previewEp = -cost
                                    root.previewHp = 0
                                    root.previewEnergy = 0
                                }
                            }
                        }
                    }
                }
            }
            ScrollBar.horizontal: ScrollBar { policy: root.hand.length > 8 ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff }
        }
    }

    Text { z: 3; anchors.left: handPanel.left; anchors.bottom: handPanel.top; text: "Your hand — drag to browse"; color: "#cbd5e1"; font.pixelSize: 13 }

    Connections {
        target: gameManager
        function onSnapshotChanged() {
            root.cancelPreview()
            root.gameSecondsLeft = selfPlayer.remainingTimeMs ? Math.ceil(selfPlayer.remainingTimeMs / 1000) : 180
        }
        function onGameError(message) { root.errorText = message }
        function onGameEnded(reason) { stack.replace("./MainMenu.qml") }
        function onGameEventsReceived(events) {
            for (let i = 0; i < events.length; ++i) {
                const event = events[i]
                if (event.eventType !== "SkillUsed") continue
                const player = root.players[event.playerIndex]
                if (!player) continue
                const characterIndex = player.activeCharacterIndex || 0
                const character = player.characters[characterIndex]
                const profile = charDataBase.details(character.characterId)
                const item = event.playerIndex === root.me
                           ? ownCharacterRepeater.itemAt(characterIndex)
                           : enemyCharacterRepeater.itemAt(characterIndex)
                if (item) item.playSkill(profile.element_type || "Physical")
            }
        }
    }

    Text { z: 4; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 12; text: root.errorText; color: "#ff7777"; font.bold: true }
}
