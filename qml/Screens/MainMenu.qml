import QtQuick
import QtQuick.Controls
import "../Components/controls"
import "../Components/common"
import "../Components/cards"
import "../Components/battle"
import "../Components/layout"


Rectangle {
    anchors.fill: parent

    // Background
    Rectangle{
        anchors.fill: parent
        gradient: Gradient{
            GradientStop{position:0;color:"#27374D"}
            GradientStop{position:1;color:"#0F172A"}
        }
    }

    // Overlay
    Rectangle{
        anchors.fill: parent

        color:"black"

        opacity:0.35
    }

    // Title

    Column {
        id: title

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 90

        spacing: 8

        Text {
            text: "✦ ✦ ✦"
            font.pixelSize: 18
            color: "#E5C07B"
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            text: "LUMIE TCG"

            font.pixelSize: 64
            font.bold: true

            color: "white"

            style: Text.Outline
            styleColor: "#202020"
        }

        Text {
            text: "The Card Adventure"

            font.pixelSize: 22
            color: "#D8D8D8"

            font.italic: true
        }

        Text {
            text: "✦ ✦ ✦"
            font.pixelSize: 18
            color: "#E5C07B"
        }
    }

    // Menu

    Column {
        anchors.top:parent.top
        anchors.left:parent.left
        spacing: 16

        Text {
            text: networkClient.connected ? "Online" : "Offline"
            color: networkClient.connected ? "lightgreen" : "tomato"
            font.pixelSize: 10
        }
    }

    Column {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        spacing: 20

        GameButton {
            height: 60
            width: 200
            text: matchmakingManager.searching ? "Cancel Matchmaking" : "Find Match"

            onClicked: {

                console.log("matchmaking")
                if (matchmakingManager.searching) {
                    matchmakingManager.cancelMatchmaking()
                } else {
                    matchmakingManager.startMatchmaking("casual_1v1", "default_deck")
                }
            }
        }

        Text {
            text: matchmakingManager.statusText
            color: "white"
            font.pixelSize: 18
        }

        Connections {
            target: matchmakingManager

            function onMatchFound(matchId, playerIndex, opponentName) {
                console.log("Match found:", matchId, playerIndex, opponentName)
                stack.push("./BattleScreen.qml")
            }

            function onMatchmakingError(message) {
                console.log("Matchmaking error:", message)
            }
        }

        Connections {
            target: networkClient

            function onErrorOccurred(error) {
                console.log("Network error:", error)
            }
        }

        GameButton {
            height: 60
            width: 200
            text: qsTr("Deck Builder");

            onClicked: {
                stack.push("./DeckScreen.qml")
            }

        }

        GameButton {
            height: 60
            width: 200
            text: qsTr("Settings");

            onClicked: {
                stack.push("./SettingsScreen.qml")
            }
        }
    }
}