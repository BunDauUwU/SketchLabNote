import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"

Rectangle {
    id: root
    anchors.fill: parent
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
    property int pendingCard: -1
    property int pendingSkill: -1
    property string previewText: ""
    property string errorText: ""

    function cancelPreview() {
        pendingCard = -1
        pendingSkill = -1
        previewText = ""
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

    // Opponent hand: identities are private, so every card stays face-down.
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
            model: root.enemyCharacters
            Rectangle {
                required property var modelData
                required property int index
                width: 132; height: 150; radius: 12
                color: index === enemyPlayer.activeCharacterIndex ? "#594b2c" : "#202938"
                border.width: index === enemyPlayer.activeCharacterIndex ? 4 : 1
                border.color: index === enemyPlayer.activeCharacterIndex ? "#f4d27a" : "#526071"
                Image {
                    anchors.fill: parent; anchors.margins: 5
                    source: assetsManager.resolveCharacterImage(modelData.characterId)
                    fillMode: Image.PreserveAspectCrop; opacity: modelData.defeated ? 0.35 : 1
                }
                Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 27; color: "#b0000000" }
                Text { anchors.left: parent.left; anchors.leftMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 6; text: modelData.characterId; color: "white"; font.pixelSize: 11 }
                Text { anchors.right: parent.right; anchors.rightMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 5; text: "♥ " + modelData.hp; color: "#ff8b8b"; font.bold: true }
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

    // Element points are deliberately vertical and use the omni asset.
    Column {
        z: 2; anchors.left: parent.left; anchors.leftMargin: 28; anchors.verticalCenter: parent.verticalCenter
        spacing: 3
        Text { text: "EP"; color: "white"; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
        Repeater {
            model: selfPlayer.elementPoints ? selfPlayer.elementPoints.current : 0
            Image { width: 29; height: 29; source: "qrc:/assets/elements/omni.png"; fillMode: Image.PreserveAspectFit }
        }
    }

    // Our character field. A second click on the same character confirms the switch.
    Row {
        id: ownField
        z: 2; anchors.bottom: handPanel.top; anchors.bottomMargin: 14
        anchors.horizontalCenter: parent.horizontalCenter; spacing: 20
        Repeater {
            model: root.selfCharacters
            Rectangle {
                required property var modelData
                required property int index
                width: 142; height: 162; radius: 12
                color: index === root.activeIndex ? "#344b43" : "#202938"
                border.width: index === root.activeIndex ? 4 : 1
                border.color: index === root.activeIndex ? "#68e0ad" : "#526071"
                Image { anchors.fill: parent; anchors.margins: 5; source: assetsManager.resolveCharacterImage(modelData.characterId); fillMode: Image.PreserveAspectCrop; opacity: modelData.defeated ? 0.35 : 1 }
                Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 28; color: "#b0000000" }
                Text { anchors.left: parent.left; anchors.leftMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 6; text: modelData.characterId; color: "white"; font.pixelSize: 11 }
                Text { anchors.right: parent.right; anchors.rightMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 5; text: "♥ " + modelData.hp; color: "#ff8b8b"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: { if (index !== root.activeIndex && !modelData.defeated) gameManager.switchCharacter(index) }
                }
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
                            if (modelData.cost <= selfPlayer.elementPoints.current)
                                gameManager.useSkill(index, modelData.cost, { playerIndex: 1 - root.me, zone: "Character", index: enemyPlayer.activeCharacterIndex })
                            root.cancelPreview()
                        } else {
                            root.pendingCard = -1; root.pendingSkill = index
                            root.previewText = modelData.name + " will cost " + modelData.cost + " EP. Click again to confirm."
                        }
                    }
                }
            }
        }
        GameButton { width: 235; height: 48; text: "End Round"; onClicked: { root.cancelPreview(); gameManager.endRound() } }
    }

    Rectangle {
        z: 3; visible: root.previewText.length > 0
        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
        width: Math.min(560, previewLabel.implicitWidth + 36); height: 48; radius: 9; color: "#d05f6670"
        Text { id: previewLabel; anchors.centerIn: parent; text: root.previewText; color: "white"; font.pixelSize: 14 }
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
                                    if (cost <= selfPlayer.elementPoints.current)
                                        gameManager.playCard(index, cost, {})
                                    root.cancelPreview()
                                } else {
                                    root.pendingSkill = -1; root.pendingCard = index
                                    root.previewText = modelData + " will cost " + cost + " EP. Click again to confirm."
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
        function onSnapshotChanged() { root.cancelPreview() }
        function onGameError(message) { root.errorText = message }
        function onGameEnded(reason) { stack.replace("./MainMenu.qml") }
    }

    Text { z: 4; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 12; text: root.errorText; color: "#ff7777"; font.bold: true }
}
