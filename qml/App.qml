import QtQuick
import QtQuick.Controls
import "./Screens"
import "./Core"

ApplicationWindow {

    id: root

    visible: true

    width: 1440
    height: 900

    minimumWidth: 1100
    minimumHeight: 700

    maximumWidth: 1920
    maximumHeight: 1200

    title: "Lumie TCG"

    SceneManager {

        anchors.fill: parent

    }
}
