import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import lumieTcg
import "../Components/controls"
import "../Components/layout"

Rectangle {
    id: root
    width: parent ? parent.width : 1280
    height: parent ? parent.height : 720
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

            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    Layout.alignment: Qt.AlignCenter
                    spacing: 30

                    GameText {
                        text: "Weather shuffle"
                        type: GameText.Heading
                    }

                    Repeater {
                        model: gameManager.weatherSequence
                        GameText {
                            required property string modelData
                            text: "✦ " + modelData
                            type: GameText.Body
                        }
                    }
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
                        spacing: 12

                        GameText {
                            text: modelData.name;
                            type: GameText.Heading;
                            Layout.alignment: Qt.AlignHCenter
                        }


                        RowLayout {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 140
                            spacing: 8

                            Repeater {
                                model: modelData.characters

                                Item {
                                    required property string modelData
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    clip: true

                                    Image {
                                        width: parent.width
                                        height: parent.height

                                        source: modelData
                                        verticalAlignment: Image.AlignTop
                                        horizontalAlignment: Image.AlignHCenter
                                        fillMode: Image.PreserveAspectCrop
                                    }
                                }
                            }
                        }


                        Item { Layout.fillHeight: true }

                        GameButton {
                            z: 1001
                            height: 64
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

        function onGamePrepared() {
            console.log("Weather data loaded:", gameManager.weatherSequence)
        }

        function onGameSnapshotReceived(snapshot) {
            stack.replace("./BattleScreen.qml")
        }
        function onGameEnded(reason) {
            stack.replace("./MainMenu.qml")
        }
    }
}
