import QtQuick
import "../controls"

GamePanel {
    id: root
    property string title: ""
    property string description: ""
    property int epDelta: 0
    property int hpDelta: 0
    property int energyDelta: 0
    property bool affordable: true
    width: 300; height: 170
    visible: title.length > 0
    backgroundColor: "#ed202938"
    borderColor: affordable ? "#d7b26d" : "#e15d5d"

    Column {
        anchors.fill: parent; anchors.margins: 16; spacing: 8
        Text { text: root.title; width: parent.width; color: "#f5dda5"; font.bold: true; font.pixelSize: 17; elide: Text.ElideRight }
        Text { text: root.description; width: parent.width; height: 66; color: "#d6dce5"; font.pixelSize: 12; wrapMode: Text.WordWrap; elide: Text.ElideRight }
        Row {
            spacing: 12
            Text { text: "EP " + root.epDelta; color: root.affordable ? "#8ed8ff" : "#ff8585"; font.bold: true }
            Text { visible: root.hpDelta !== 0; text: "HP " + root.hpDelta; color: root.hpDelta < 0 ? "#ff8585" : "#78e4a8"; font.bold: true }
            Text { visible: root.energyDelta !== 0; text: "Energy " + root.energyDelta; color: "#f2ce69"; font.bold: true }
        }
        Text { text: root.affordable ? "Click again to confirm" : "Not enough Element Points"; color: root.affordable ? "#9ee5bd" : "#ff8585"; font.pixelSize: 11 }
    }
}
