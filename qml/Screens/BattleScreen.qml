// qml/Screens/BattleScreen.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"

Rectangle {
    id: root

    anchors.fill: parent

    property int ownElementPoints: 10
    property int ownMaxElementPoints: 10
    property int opponentElementPoints: 10
    property int opponentMaxElementPoints: 10
    property string activeWeather: "Rain"
    property string weatherDescription: "Battlefield condition placeholder. Logic hooks can fill this from snapshots later."

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#111722" }
            GradientStop { position: 0.45; color: "#23202B" }
            GradientStop { position: 1.0; color: "#111016" }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 2
        border.color: Qt.rgba(Theme.primary.r, Theme.primary.g, Theme.primary.b, 0.22)
        anchors.margins: Spacing.lg
        radius: Radius.xl
    }

    WeatherBanner {
        id: weatherBanner
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: Spacing.lg
        weatherName: root.activeWeather
        description: root.weatherDescription
        remainingRounds: 2
    }

    GamePanel {
        id: opponentPanel
        width: 420
        height: 148
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: Spacing.xl

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: Spacing.md
            spacing: Spacing.sm

            GameText {
                text: gameManager.opponentName.length > 0 ? gameManager.opponentName : "Opponent"
                type: GameText.Heading
                Layout.fillWidth: true
            }

            ElementPointBar {
                current: root.opponentElementPoints
                maximum: root.opponentMaxElementPoints
                label: "Opponent EP"
                Layout.fillWidth: true
            }
        }
    }

    Item {
        id: battlefield
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: weatherBanner.bottom
        anchors.bottom: actionDock.top
        anchors.margins: Spacing.xl

        Repeater {
            model: [
                { name: "Enemy A", hp: "10", xPos: 0.28, yPos: 0.24 },
                { name: "Enemy B", hp: "10", xPos: 0.50, yPos: 0.16 },
                { name: "Enemy C", hp: "10", xPos: 0.72, yPos: 0.24 },
                { name: "Hero A", hp: "10", xPos: 0.28, yPos: 0.70 },
                { name: "Hero B", hp: "10", xPos: 0.50, yPos: 0.78 },
                { name: "Hero C", hp: "10", xPos: 0.72, yPos: 0.70 }
            ]

            GamePanel {
                required property var modelData

                width: 150
                height: 190
                x: battlefield.width * modelData.xPos - width / 2
                y: battlefield.height * modelData.yPos - height / 2
                highlighted: modelData.name === "Hero B"
                scale: highlighted ? 1.06 : 1.0

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: Spacing.sm
                    spacing: Spacing.xs

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        radius: Radius.md
                        color: Qt.rgba(1, 1, 1, 0.08)
                        border.width: 1
                        border.color: Qt.rgba(1, 1, 1, 0.14)

                        GameText {
                            anchors.centerIn: parent
                            text: "✦"
                            type: GameText.Display
                            color: Qt.rgba(Theme.primary.r, Theme.primary.g, Theme.primary.b, 0.80)
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        GameText {
                            text: modelData.name
                            type: GameText.Caption
                            Layout.fillWidth: true
                        }

                        GameText {
                            text: "♥ " + modelData.hp
                            type: GameText.Caption
                            color: Theme.danger
                        }
                    }
                }
            }
        }
    }

    GamePanel {
        id: actionDock
        height: 176
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: Spacing.xl
        radiusSize: Radius.xl

        RowLayout {
            anchors.fill: parent
            anchors.margins: Spacing.lg
            spacing: Spacing.lg

            ElementPointBar {
                current: root.ownElementPoints
                maximum: root.ownMaxElementPoints
                label: "Your EP"
                Layout.preferredWidth: 390
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: Spacing.md

                Repeater {
                    model: ["Attack", "Skill", "Card", "Switch"]

                    GameButton {
                        required property string modelData

                        Layout.preferredWidth: 132
                        Layout.preferredHeight: 58
                        text: modelData
                        onClicked: {
                            if (modelData === "Skill") {
                                gameManager.useSkill(0, 3, { playerIndex: 1, zone: "Character", index: 0 })
                            }
                        }
                    }
                }
            }

            GameButton {
                Layout.preferredWidth: 150
                Layout.preferredHeight: 58
                text: "End Round"
                onClicked: gameManager.endRound()
            }
        }
    }

    GamePanel {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: Spacing.xl
        width: 300
        height: 132

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: Spacing.md
            spacing: Spacing.xs

            GameText {
                text: "Match: " + (gameManager.matchId.length > 0 ? gameManager.matchId : "local-preview")
                type: GameText.Caption
                color: Theme.textGray
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            GameText {
                text: "Stage: " + gameManager.stage
                type: GameText.Caption
                color: Theme.textGray
            }

            GameText {
                text: "Visual client shell"
                type: GameText.Caption
                color: Theme.primary
            }
        }
    }

    Connections {
        target: gameManager

        function onGameSnapshotReceived(snapshot) {
            console.log("Snapshot received:", JSON.stringify(snapshot))
        }

        function onGameEventsReceived(events) {
            console.log("Events received:", JSON.stringify(events))
        }

        function onGameError(message) {
            console.log("Game error:", message)
        }

        function onGameEnded(reason) {
            console.log("Game ended:", reason)
        }
    }
}
