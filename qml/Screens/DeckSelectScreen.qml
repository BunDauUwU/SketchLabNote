import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/controls"
import "../Components/layout"

Rectangle {
    id: root
    anchors.fill: parent
    color: "#101827"
    property int secondsLeft: gameManager.selectionSeconds
    property bool selected: false

    Component.onCompleted: deckManager.refreshValidDecks(authManager.username)

    Timer {
        interval: 1000
        running: !root.selected && root.secondsLeft > 0
        repeat: true
        onTriggered: root.secondsLeft--
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 48
        spacing: 22

        GameText {
            text: root.selected ? "Waiting for opponent..." : "Select a battle deck — " + root.secondsLeft + "s"
            type: GameText.Display
            Layout.alignment: Qt.AlignHCenter
        }

        GamePanel {
            Layout.fillWidth: true
            Layout.preferredHeight: 90
            RowLayout {
                anchors.centerIn: parent
                spacing: 30
                GameText { text: "Weather shuffle"; type: GameText.Heading }
                Repeater {
                    model: gameManager.weatherSequence
                    GameText { required property string modelData; text: "✦ " + modelData; type: GameText.Body }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 24
            Repeater {
                model: deckManager.validDecks
                GamePanel {
                    id: deckOption
                    required property var modelData
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    enabled: !root.selected && root.secondsLeft > 0
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 22
                        GameText { text: modelData.name; type: GameText.Heading; Layout.alignment: Qt.AlignHCenter }
                        Repeater {
                            model: modelData.characters
                            GamePanel {
                                required property string modelData
                                Layout.fillWidth: true
                                Layout.preferredHeight: 64
                                GameText { anchors.centerIn: parent; text: modelData; type: GameText.Body }
                            }
                        }
                        Item { Layout.fillHeight: true }
                        GameText { text: "30 cards"; type: GameText.Caption; Layout.alignment: Qt.AlignHCenter }
                        GameButton {
                            text: "Play this deck"
                            Layout.fillWidth: true
                            onClicked: {
                                gameManager.selectDeck(deckOption.modelData.deckId,
                                                       deckOption.modelData.characters,
                                                       deckOption.modelData.cards)
                                root.selected = true
                            }
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: gameManager
        function onGameSnapshotReceived(snapshot) {
            stack.replace("./BattleScreen.qml")
        }
        function onGameEnded(reason) {
            stack.replace("./MainMenu.qml")
        }
    }
}
