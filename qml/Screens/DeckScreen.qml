import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/controls"
import "../Core/CardDescription.js" as Description

Rectangle {
    id: root
    implicitWidth: 1280
    implicitHeight: 720
    color: "#121923"

    property bool browseCharacters: false
    property var cardCatalog: makeCatalog(cardDataBase.cardList, false)
    property var characterCatalog: makeCatalog(charDataBase.characterList, true)
    property string inspectedId: ""
    property bool inspectedCharacter: false
    property var inspected: ({})
    property string message: ""

    Component.onCompleted: deckManager.loadDeck(authManager.username)

    function makeCatalog(sources, character) {
        const result = [];
        const seen = {};
        for (let i = 0; i < sources.length; ++i) {
            const id = character ? charDataBase.name(i) : cardDataBase.name(i);
            const detail = character ? charDataBase.details(id) : cardDataBase.details(id);
            const normalized = id.replace(/[^a-z0-9]/gi, "").toLowerCase();
            if (seen[normalized] || (character ? !detail.skills : detail.cost === undefined && detail.tag === undefined))
                continue;
            seen[normalized] = true;
            result.push(id);
        }
        return result;
    }
    function inspect(id, character) {
        inspectedId = id;
        inspectedCharacter = character;
        inspected = character ? charDataBase.details(id) : cardDataBase.details(id);
    }
    function selectDeck(index) {
        if (index === deckManager.deckIndex)
            return;
        deckManager.changeDeckIndex(index - deckManager.deckIndex);
        deckManager.loadDeck(authManager.username);
        message = "";
    }
    function add(id, character) {
        inspect(id, character);
        message = "";
        if (character) {
            deckManager.addCharacter(id, authManager.username);
            return;
        }
        const required = cardDataBase.requiredCharacter(id);
        const normalize = function (value) {
            return String(value).replace(/[^a-z0-9]/gi, "").toLowerCase();
        };
        if (required && !deckManager.characters.some(function (value) {
            return normalize(value) === normalize(required);
        })) {
            message = "Add " + required + " to this deck before adding this card.";
            return;
        }
        deckManager.addCard(id, authManager.username);
    }

    component CardTile: Rectangle {
        id: tile
        required property string entryId
        property bool characterTile: false
        property bool inDeck: false
        width: 92
        height: 120
        radius: 7
        color: "#273548"
        border.color: root.inspectedId === entryId ? "#e5c680" : "#52627a"
        border.width: root.inspectedId === entryId ? 2 : 1
        Image {
            anchors.fill: parent
            anchors.margins: 4
            source: tile.characterTile ? assetsManager.resolveCharacterImage(tile.entryId) : assetsManager.resolveCardImage(tile.entryId)
            fillMode: Image.PreserveAspectFit
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onEntered: root.inspect(tile.entryId, tile.characterTile)
            onClicked: {
                root.inspect(tile.entryId, tile.characterTile);
                if (!tile.inDeck)
                    root.add(tile.entryId, tile.characterTile);
                else if (tile.characterTile)
                    deckManager.removeCharacter(tile.entryId, authManager.username);
                else
                    deckManager.removeCard(tile.entryId, authManager.username);
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 14
        RowLayout {
            Layout.fillWidth: true
            GameButton {
                text: "Back"
                Layout.preferredWidth: 90
                onClicked: stack.pop()
            }
            Text {
                text: "Deck builder"
                color: "white"
                font.pixelSize: 23
                font.bold: true
            }
            Item {
                Layout.fillWidth: true
            }
            Repeater {
                model: 3
                GameButton {
                    required property int index
                    text: (deckManager.deckIndex === index + 1 ? "✓ " : "") + "Deck " + (index + 1)
                    Layout.preferredWidth: 115
                    enabled: deckManager.deckIndex !== index + 1
                    onClicked: root.selectDeck(index + 1)
                }
            }
        }
        Text {
            text: root.message || "Click a collection entry to add it. Click an entry in your deck to remove it. Changes save automatically."
            color: root.message ? "#ff9797" : "#b5c3d8"
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 16
            Rectangle {
                Layout.preferredWidth: 410
                Layout.fillHeight: true
                radius: 10
                color: "#1d2838"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    RowLayout {
                        GameButton {
                            text: "Cards"
                            enabled: root.browseCharacters
                            onClicked: root.browseCharacters = false
                        }
                        GameButton {
                            text: "Characters"
                            enabled: !root.browseCharacters
                            onClicked: root.browseCharacters = true
                        }
                    }
                    GridView {
                        id: collection
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        cellWidth: 96
                        cellHeight: 126
                        model: root.browseCharacters ? root.characterCatalog : root.cardCatalog
                        ScrollBar.vertical: ScrollBar {}
                        delegate: CardTile {
                            required property string modelData
                            required property int index
                            entryId: modelData
                            characterTile: root.browseCharacters
                        }
                    }
                }
            }
            Rectangle {
                Layout.preferredWidth: 440
                Layout.fillHeight: true
                radius: 10
                color: "#202f40"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 10
                    Text {
                        text: "Deck " + deckManager.deckIndex + " · Characters " + deckManager.characters.length + "/3"
                        color: "#e5c680"
                        font.bold: true
                    }
                    Row {
                        spacing: 10
                        Layout.preferredHeight: 120
                        Repeater {
                            model: deckManager.characters
                            CardTile {
                                required property string modelData
                                entryId: modelData
                                characterTile: true
                                inDeck: true
                            }
                        }
                    }
                    Text {
                        text: "Cards " + deckManager.cards.length + "/30 · up to 3 copies each"
                        color: "#e5c680"
                        font.bold: true
                    }
                    GridView {
                        // Layout.fillWidth: true
                        width: 400
                        Layout.fillHeight: true
                        clip: true
                        cellWidth: 60.6
                        cellHeight: 66
                        model: deckManager.cards
                        delegate: CardTile {
                            required property string modelData
                            entryId: modelData
                            inDeck: true
                            width: 77
                            height: 102
                        }
                    }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.minimumWidth: 260
                Layout.fillHeight: true
                radius: 10
                color: "#1d2838"
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    Text {
                        text: root.inspectedId ? (root.inspected.name || root.inspectedId).replace(/([a-z])([A-Z])/g, "$1 $2") : "Card details"
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        color: "#e5c680"
                        font.pixelSize: 19
                        font.bold: true
                    }
                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        contentWidth: availableWidth
                        Text {
                            width: parent.width
                            text: !root.inspectedId ? "Hover over a card or character to read its cost, effects and requirements." : root.inspectedCharacter ? Description.describeCharacter(root.inspected) : Description.describe(root.inspected)
                            color: "#d9e2ef"
                            font.pixelSize: 14
                            wrapMode: Text.WordWrap
                            textFormat: Text.PlainText
                        }
                    }
                }
            }
        }
    }
    Connections {
        target: deckManager
        function onErrorOccurred(message) {
            root.message = message;
        }
    }
}
