// qml/Screens/BattleScreen.qml
import QtQuick
import QtQuick.Controls

Item {
    id: root

    width: 1280
    height: 720

    Column {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 32
        spacing: 12

        Text {
            text: "Match: " + gameManager.matchId
            color: "white"
        }

        Text {
            text: "Opponent: " + gameManager.opponentName
            color: "white"
        }

        Text {
            text: "Stage: " + gameManager.stage
            color: "white"
        }

        Button {
            text: "Choose Character 0"
            onClicked: gameManager.chooseActiveCharacter(0)
        }

        Button {
            text: "Use Skill 0"
            onClicked: {
                gameManager.useSkill(
                    0,
                    3,
                    {
                        playerIndex: 1,
                        zone: "Character",
                        index: 0
                    }
                )
            }
        }

        Button {
            text: "End Round"
            onClicked: gameManager.endRound()
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