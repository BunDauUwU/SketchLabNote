import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../Components/battle"
import "../Components/controls"

Rectangle {
    id : root

    anchors.fill: parent
        Column {
            id : characterSetup
            height: 660
            width : 600
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            Rectangle {
                id: characterHolder

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: 20


                height: 120
                width: 600
                color: "red"
            }

            Rectangle {
                id : characterStorage

                anchors.left: parent.left
                anchors.top: characterHolder.bottom
                anchors.topMargin: 20

                height: 460
                width: 600
                color: "blue"

                GridView {
                        id: characterGrid
                        anchors.fill: parent
                        anchors.margins: 20
                        cellWidth: 140
                        cellHeight: 180
                        clip: true

                        model: charDataBase.characterList

                        delegate: Rectangle {
                            width: characterGrid.cellWidth - 10
                            height: characterGrid.cellHeight - 10
                            color: "#1e1e1e"
                            radius: 5
                            border.color: "#333333"

                            Image {
                                id: charImage
                                anchors.fill: parent
                                anchors.margins: 5

                                source: modelData
                                fillMode: Image.PreserveAspectFit

                                onStatusChanged: {
                                    if (status === Image.Error) {
                                        console.log("QML Lỗi hiển thị ảnh tại nguồn:", source)
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    charDataBase.handlecharacterClick(index)
                                }
                            }
                        }
                    }
            }
        }

        Column {
            id : cardSetup
            height: 660
            width : 600
            anchors.top : parent.top
            anchors.right: parent.right
            anchors.rightMargin: 20

            Rectangle {
                id: cardHolder

                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 20


                height: 120
                width: 600
                color: "yellow"
            }

            Rectangle {
                id : cardStorage

                anchors.right: parent.right
                anchors.top: cardHolder.bottom
                anchors.topMargin: 20

                height: 460
                width: 600
                color: "green"

                GridView {
                        id: cardGrid
                        anchors.fill: parent
                        anchors.margins: 20
                        cellWidth: 140
                        cellHeight: 180
                        clip: true

                        model: cardDataBase.cardList

                        delegate: Rectangle {
                            width: cardGrid.cellWidth - 10
                            height: cardGrid.cellHeight - 10
                            color: "#1e1e1e"
                            radius: 5
                            border.color: "#333333"

                            Image {
                                id: cardImage
                                anchors.fill: parent
                                anchors.margins: 5

                                source: modelData
                                fillMode: Image.PreserveAspectFit

                                onStatusChanged: {
                                    if (status === Image.Error) {
                                        console.log("QML Lỗi hiển thị ảnh tại nguồn:", source)
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    cardDataBase.handlecardClick(index)
                                }
                            }
                        }
                    }

            }
        }



        GameButton {
            id : saveDeck
            GameText {
                text : "Save"
            }
        }

}