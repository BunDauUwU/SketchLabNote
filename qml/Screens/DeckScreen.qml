import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/controls"

Rectangle {
    id: root
    anchors.fill: parent
    color: "#101722"
    property string inspectedType: "character"
    property string inspectedId: ""
    property var inspected: ({})

    function inspectCharacter(id) { inspectedType = "character"; inspectedId = id; inspected = charDataBase.details(id) }
    function inspectCard(id) { inspectedType = "card"; inspectedId = id; inspected = cardDataBase.details(id) }

    Component.onCompleted: deckManager.loadDeck(authManager.username)

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#172335" }
            GradientStop { position: 0.55; color: "#242433" }
            GradientStop { position: 1; color: "#111824" }
        }
    }

    RowLayout {
        anchors.fill: parent; anchors.margins: 22; spacing: 16

        GamePanel {
            Layout.preferredWidth: 445; Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent; anchors.margins: 14; spacing: 10
                RowLayout {
                    Layout.fillWidth: true
                    GameText { text: "Character Archive"; type: GameText.Heading; Layout.fillWidth: true }
                    GameText { text: deckManager.characters.length + "/3"; type: GameText.Body; color: Theme.primary }
                }
                GridView {
                    id: characterGrid
                    Layout.fillWidth: true; Layout.preferredHeight: 238
                    cellWidth: 100; cellHeight: 112; clip: true
                    model: charDataBase.characterList
                    ScrollBar.vertical: ScrollBar { }
                    delegate: Rectangle {
                        required property string modelData; required property int index
                        width: 92; height: 104; radius: 9; color: "#263247"; border.color: "#53657d"
                        Image { anchors.fill: parent; anchors.margins: 4; source: modelData; fillMode: Image.PreserveAspectCrop }
                        Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 23; color: "#b8000000" }
                        Text { anchors.centerIn: parent; anchors.verticalCenterOffset: 40; width: 86; text: charDataBase.name(index); color: "white"; font.pixelSize: 10; horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight }
                        MouseArea {
                            anchors.fill: parent; hoverEnabled: true
                            onEntered: root.inspectCharacter(charDataBase.name(index))
                            onClicked: deckManager.addCharacter(charDataBase.name(index), authManager.username)
                        }
                    }
                }

                GameText { text: "Selected Party"; type: GameText.Heading }
                Row {
                    Layout.fillWidth: true; Layout.preferredHeight: 130; spacing: 10
                    Repeater {
                        model: deckManager.characters
                        Rectangle {
                            required property string modelData
                            width: 126; height: 126; radius: 10; color: "#324151"; border.width: 2; border.color: Theme.primary
                            Image { anchors.fill: parent; anchors.margins: 5; source: assetsManager.resolveCharacterImage(modelData); fillMode: Image.PreserveAspectCrop }
                            Rectangle { anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; height: 25; color: "#c0000000" }
                            Text { anchors.centerIn: parent; anchors.verticalCenterOffset: 48; width: 118; text: modelData; color: "white"; font.pixelSize: 10; horizontalAlignment: Text.AlignHCenter; elide: Text.ElideRight }
                            MouseArea { anchors.fill: parent; hoverEnabled: true; onEntered: root.inspectCharacter(modelData); onClicked: deckManager.removeCharacter(modelData, authManager.username) }
                        }
                    }
                }

                GameText { text: "Card Archive"; type: GameText.Heading }
                GridView {
                    id: cardGrid
                    Layout.fillWidth: true; Layout.fillHeight: true
                    cellWidth: 84; cellHeight: 112; clip: true
                    model: cardDataBase.cardList
                    ScrollBar.vertical: ScrollBar { }
                    delegate: Rectangle {
                        required property string modelData; required property int index
                        width: 76; height: 104; radius: 8; color: "#263247"; border.color: "#53657d"
                        Image { anchors.fill: parent; anchors.margins: 3; source: modelData; fillMode: Image.PreserveAspectFit }
                        MouseArea {
                            anchors.fill: parent; hoverEnabled: true
                            onEntered: root.inspectCard(cardDataBase.name(index))
                            onClicked: deckManager.addCard(cardDataBase.name(index), authManager.username)
                        }
                    }
                }
            }
        }

        GamePanel {
            Layout.preferredWidth: 410; Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent; anchors.margins: 14; spacing: 10
                RowLayout {
                    Layout.fillWidth: true
                    GameText { text: "Deck " + deckManager.deckIndex; type: GameText.Title; Layout.fillWidth: true }
                    GameButton { text: "‹"; Layout.preferredWidth: 44; onClicked: { deckManager.changeDeckIndex(-1); deckManager.loadDeck(authManager.username) } }
                    GameButton { text: "›"; Layout.preferredWidth: 44; onClicked: { deckManager.changeDeckIndex(1); deckManager.loadDeck(authManager.username) } }
                }
                GameText {
                    text: deckManager.characters.length === 3 && deckManager.cards.length === 30 ? "✓ Battle ready" : "Needs 3 characters and 30 cards"
                    color: deckManager.characters.length === 3 && deckManager.cards.length === 30 ? Theme.success : Theme.danger
                    type: GameText.Body
                }
                GridView {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    cellWidth: 76; cellHeight: 100; clip: true
                    model: deckManager.cards
                    ScrollBar.vertical: ScrollBar { }
                    delegate: Rectangle {
                        required property string modelData
                        width: 68; height: 92; radius: 7; color: "#273449"; border.color: "#8f7a52"
                        Image { anchors.fill: parent; anchors.margins: 3; source: assetsManager.resolveCardImage(modelData); fillMode: Image.PreserveAspectFit }
                        MouseArea { anchors.fill: parent; hoverEnabled: true; onEntered: root.inspectCard(modelData); onClicked: deckManager.removeCard(modelData, authManager.username) }
                    }
                }
                GameText { text: deckManager.cards.length + " / 30 cards  •  Click a selected item to remove"; type: GameText.Caption; color: Theme.textGray }
            }
        }

        GamePanel {
            Layout.fillWidth: true; Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent; anchors.margins: 20; spacing: 12
                GameText { text: "Details"; type: GameText.Title }
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter; Layout.preferredWidth: 220; Layout.preferredHeight: 286
                    radius: 14; color: "#1d293a"; border.width: 2; border.color: Theme.primary
                    Image {
                        anchors.fill: parent; anchors.margins: 8
                        source: root.inspectedType === "character" ? assetsManager.resolveCharacterImage(root.inspectedId) : assetsManager.resolveCardImage(root.inspectedId)
                        fillMode: Image.PreserveAspectFit
                    }
                }
                GameText { text: root.inspected.name || "Select a card or character"; type: GameText.Heading; Layout.fillWidth: true; wrapMode: Text.WordWrap }
                GameText {
                    visible: root.inspectedType === "character" && root.inspectedId.length > 0
                    text: (root.inspected.element_type || "Unknown") + "  •  " + (root.inspected.weapon || "Unknown") + "\nHP " + (root.inspected.hp || 0) + "  •  Max Energy " + (root.inspected.energy || 0)
                    type: GameText.Body; color: "#d7e3f3"; Layout.fillWidth: true
                }
                GameText {
                    visible: root.inspectedType === "card" && root.inspectedId.length > 0
                    text: "Cost " + (root.inspected.costValue || 0) + " EP\n" + (root.inspected.tag || "Action card")
                    type: GameText.Body; color: "#d7e3f3"; Layout.fillWidth: true; wrapMode: Text.WordWrap
                }
                GameText { text: root.inspectedType === "character" ? "Skills" : "Effect summary"; type: GameText.Heading; visible: root.inspectedId.length > 0 }
                Repeater {
                    model: root.inspectedType === "character" ? (root.inspected.skillList || []) : []
                    GamePanel {
                        required property var modelData
                        Layout.fillWidth: true; Layout.preferredHeight: 52
                        backgroundColor: "#b52a3749"
                        RowLayout { anchors.fill: parent; anchors.margins: 9; GameText { text: modelData.name; type: GameText.Caption; Layout.fillWidth: true; elide: Text.ElideRight }; GameText { text: modelData.cost + " EP"; type: GameText.Caption; color: Theme.primary } }
                    }
                }
                Item { Layout.fillHeight: true }
                GameButton { text: "Back"; Layout.fillWidth: true; onClicked: stack.pop() }
            }
        }
    }
}
