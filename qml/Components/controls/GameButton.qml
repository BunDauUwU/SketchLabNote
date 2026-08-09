import QtQuick
import QtQuick.Controls
import "../../Core"

Rectangle {
    id : root
    property alias text: label.text

    property color backgroundColor: Theme.panelBackground

    property color accentColor: Theme.primary

    // property bool enabled: true

    signal clicked()

    scale: mouse.pressed ? 0.97 : mouse.containsMouse ? 1.03 : 1.0

    Behavior on scale{

        NumberAnimation{

            duration: Motion.Fast

        }

    }

    color: mouse.pressed ? Theme.primary:mouse.containsMouse ? Theme.secondary:backgroundColor

    border.width:2

    border.color:accentColor

    HoverHandler {
            cursorShape: Qt.PointingHandCursor
    }

    GameText{

        id:label

        anchors.centerIn:parent

    }

    TapHandler {
            onTapped: root.clicked()
        }
}
