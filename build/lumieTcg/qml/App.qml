import QtQuick
import QtQuick.Controls
import "./Screens"
import "./Core"

ApplicationWindow {

    id: root

    visible: true

    width: 1280
    height: 720

    minimumWidth: 1280
    minimumHeight: 720

    maximumWidth: 1280
    maximumHeight: 720

    title: "Lumie TCG"

    SceneManager {

        anchors.fill: parent

    }
}

