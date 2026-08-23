import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"

Rectangle {
    id: root

    implicitWidth: 1280
    implicitHeight: 720

    color: "#121212"

    property int characterWidth: 460
    property int cardWidth: 760
    property string hoveredCardName: ""
    property string hoveredCardSkills: ""
    property string hoveredCharacterName: ""
    property string hoveredCharacterSkills: ""

    property bool infoVisible: false

    Component.onCompleted: {
        deckManager.loadDeck(authManager.username)
    }

    // =========================================================
    // CHARACTER STORAGE
    // =========================================================

    Rectangle {
        id: characterStorage

        width: root.characterWidth
        height: 275/2

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 20

        color: "#20242a"
        radius: 8
        border.color: "#333333"

        GridView {
            id: characterGrid

            anchors.fill: parent
            anchors.margins: 15

            cellWidth: 105
            cellHeight: 125

            clip: true

            model: charDataBase.characterList

            delegate: Rectangle {
                width: characterGrid.cellWidth - 8
                height: characterGrid.cellHeight - 8

                color: "#1e1e1e"
                radius: 6
                border.color: "#333333"

                Image {
                    id: charImage

                    width: parent.width - 12
                    height: parent.height - 12

                    anchors.centerIn: parent

                    source: modelData
                    fillMode: Image.PreserveAspectFit

                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log(
                                "Character image error:",
                                source
                            )
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true

                    onEntered: {
                        root.hoveredCharacterName =
                            charDataBase.name(index)

                        root.hoveredCharacterSkills =
                            charDataBase.skills(index)

                        root.hoveredCardName = ""
                        root.hoveredCardSkills = ""

                        root.infoVisible = true
                    }

                    // onExited: {
                    //     root.infoVisible = false
                    // }

                    onClicked: {
                        charDataBase.handlecharacterClick(index)

                        deckManager.addCharacter(
                            modelData,
                            authManager.username
                        )
                    }
                }
            }
        }
    }

    // =========================================================
    // CHARACTER HOLDER
    // =========================================================

    Rectangle {
        id: characterHolder

        width: 325
        height: 275/2

        anchors.left: characterStorage.right
        anchors.top: characterStorage.top
        anchors.leftMargin: 20

        color: "#292d33"
        radius: 8
        border.color: "#333333"

        GridView {
            id: charDeckGrid

            anchors.fill: parent
            anchors.margins: 15

            cellWidth: 95
            cellHeight: 125

            clip: true
            interactive: false

            model: deckManager.characters

            delegate: Rectangle {
                width: charDeckGrid.cellWidth - 8
                height: charDeckGrid.cellHeight - 8

                color: "#1e1e1e"
                radius: 6
                border.color: "#333333"

                Image {
                    id: charDeckImage

                    width: parent.width - 12
                    height: parent.height - 12

                    anchors.centerIn: parent

                    source: modelData
                    fillMode: Image.PreserveAspectFit

                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log(
                                "Character deck image error:",
                                source
                            )
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true

                    onEntered: {
                        root.hoveredCharacterName =
                            charDataBase.name(index)

                        root.hoveredCharacterSkills =
                            charDataBase.skills(index)

                        root.hoveredCardName = ""
                        root.hoveredCardSkills = ""

                        root.infoVisible = true
                    }

                    // onExited: {
                    //     root.infoVisible = false
                    // }

                    onClicked: {
                        deckManager.removeCharacter(
                            modelData,
                            authManager.username
                        )
                    }
                }
            }
        }
    }

    // =========================================================
    // CARD STORAGE
    // =========================================================

    Rectangle {
        id: cardStorage

        width: 490
        height: 355+275/2

        anchors.left: parent.left
        anchors.top: characterStorage.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20

        color: "#20242a"
        radius: 8
        border.color: "#333333"

        GridView {
            id: cardGrid

            anchors.fill: parent
            anchors.margins: 15

            cellWidth: 115
            cellHeight: 145

            clip: true

            model: cardDataBase.cardList

            delegate: Rectangle {
                width: cardGrid.cellWidth - 8
                height: cardGrid.cellHeight - 8

                color: "#1e1e1e"
                radius: 6
                border.color: "#333333"

                Image {
                    id: cardImage

                    width: parent.width - 10
                    height: parent.height - 10

                    anchors.centerIn: parent

                    source: modelData
                    fillMode: Image.PreserveAspectFit

                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log(
                                "Card image error:",
                                source
                            )
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true

                    onEntered: {
                        root.hoveredCardName =
                            cardDataBase.name(index)

                        root.hoveredCardSkills =
                            cardDataBase.skills(index)

                        root.hoveredCharacterName = ""
                        root.hoveredCharacterSkills = ""

                        root.infoVisible = true
                    }

                    // onExited: {
                    //     root.infoVisible = false
                    // }

                    onClicked: {
                        cardDataBase.handlecardClick(index)

                        deckManager.addCard(
                            modelData,
                            authManager.username
                        )
                    }
                }
            }
        }
    }

    // =========================================================
    // CARD HOLDER
    // =========================================================

    Rectangle {
        id: cardHolder

        width: 460
        height: 355+275/2

        anchors.left: cardStorage.right
        anchors.top: cardStorage.top
        anchors.leftMargin: 20

        color: "#292d33"
        radius: 8
        border.color: "#333333"

        GridView {
            id: cardDeckGrid

            anchors.fill: parent
            anchors.margins: 15

            cellWidth: 70
            cellHeight: 90

            clip: true

            model: deckManager.cards

            onCountChanged: {
                positionViewAtEnd()
            }

            delegate: Rectangle {
                width: cardDeckGrid.cellWidth - 8
                height: cardDeckGrid.cellHeight - 8

                color: "#1e1e1e"
                radius: 6
                border.color: "#333333"

                Image {
                    id: cardDeckImage

                    width: parent.width - 10
                    height: parent.height - 10

                    anchors.centerIn: parent

                    source: modelData
                    fillMode: Image.PreserveAspectFit

                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log(
                                "Deck card image error:",
                                source
                            )
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    hoverEnabled: true

                    onEntered: {
                        root.hoveredCardName =
                            cardDataBase.name(index)

                        root.hoveredCardSkills =
                            cardDataBase.skills(index)

                        root.hoveredCharacterName = ""
                        root.hoveredCharacterSkills = ""

                        root.infoVisible = true
                    }

                    // onExited: {
                    //     root.infoVisible = false
                    // }

                    onClicked: {
                        deckManager.removeCard(
                            modelData,
                            authManager.username
                        )
                    }
                }
            }
        }
    }

    // =========================================================
    // DECK NAVIGATION
    // =========================================================

    Row {
        id: utilityButtons

        spacing: 15

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.rightMargin: 20
        anchors.bottomMargin: 15

        z:101

        GameButton {
            id: previousDeck

            width: 120
            height: 50

            text: "<"

            onClicked: {
                deckManager.changeDeckIndex(-1)
                deckManager.loadDeck(authManager.username)
            }
        }

        GameButton {
            id: nextDeck

            width: 120
            height: 50

            text: ">"

            onClicked: {
                deckManager.changeDeckIndex(1)
                deckManager.loadDeck(authManager.username)
            }
        }

        GameButton {
            id: backToMain

            width: 120
            height: 50

            text: "Back"

            onClicked: {
                stack.replace("./MainMenu.qml")
            }
        }
    }


    // =========================================================
    // INFORMATION PANEL
    // =========================================================

    Rectangle {
        id: infoPanel

        width: 260
        height: parent.height-20

        anchors.right: parent.right
        anchors.top: parent.top

        anchors.rightMargin: 20
        anchors.topMargin: 20

        radius: 10

        color: "#1b1e23"
        border.width: 1
        border.color: "#555b66"

        visible: root.infoVisible

        z: 100

        Column {
            anchors.fill: parent
            anchors.margins: 20

            spacing: 12

            Text {
                id: infoName

                width: parent.width

                text: {
                    if (root.hoveredCardName !== "")
                        return root.hoveredCardName

                    return root.hoveredCharacterName
                }

                color: "#ffffff"

                font.pixelSize: 22
                fontSizeMode: Text.Fit;
                font.bold: true

                wrapMode: Text.WordWrap
            }

            Rectangle {
                width: parent.width
                height: 1

                color: "#555b66"
            }

            ScrollView {
                width: parent.width
                height: parent.height - infoName.height
                clip: true
            Text {
                id: infoSkills

                width: parent.width
                height: parent.height - infoName.height - 200

                text: {
                    if (root.hoveredCardSkills !== "")
                        return root.hoveredCardSkills

                    return root.hoveredCharacterSkills
                }

                color: "#d0d4da"

                font.pixelSize: 15

                wrapMode: Text.WordWrap
                textFormat: Text.PlainText

                verticalAlignment: Text.AlignTop

                elide: Text.ElideRight
            }
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 120
            }
        }
    }
}