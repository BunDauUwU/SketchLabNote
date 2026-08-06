import QtQuick
import QtQuick.Controls
import "./Screens"
import "./Core"

ApplicationWindow {

    id: root

    visible: true

    width: 1600
    height: 900

    minimumWidth: 1280
    minimumHeight: 720

    title: "Lumie TCG"

    SceneManager {

        anchors.fill: parent

    }
}

