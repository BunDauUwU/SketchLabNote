import QtQuick
import "../controls"

Item {
    id: root
    property var character: ({ characterId: "", hp: 0, energy: 0, defeated: false })
    property var profile: ({ weapon: "", element_type: "" })
    property bool active: false
    property bool opponent: false
    property bool selectable: false
    property string elementFlash: ""
    signal switchRequested()

    width: 142
    height: 162

    function attackStyle() {
        const weapon = String(profile.weapon || "").toLowerCase()
        if (weapon.indexOf("bow") >= 0) return "bow"
        if (weapon.indexOf("claymore") >= 0) return "claymore"
        if (weapon.indexOf("catalyst") >= 0) return "catalyst"
        return "sword"
    }

    function playSkill(element) {
        elementFlash = element || profile.element_type || "Physical"
        attackAnimation.restart()
        elementalBurst.play(elementFlash)
    }

    Rectangle {
        id: card
        anchors.fill: parent
        radius: 12
        color: root.active ? (root.opponent ? "#594b2c" : "#344b43") : "#202938"
        border.width: root.active ? 4 : 1
        border.color: root.active ? (root.opponent ? "#f4d27a" : "#68e0ad") : "#526071"

        Image {
            anchors.fill: parent
            anchors.margins: 5
            source: assetsManager.resolveCharacterImage(root.character.characterId || "")
            fillMode: Image.PreserveAspectCrop
            opacity: root.character.defeated ? 0.35 : 1
        }
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom
            height: 29; color: "#c0000000"
        }
        Text {
            anchors.left: parent.left; anchors.leftMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 7
            width: parent.width - 52; text: root.character.characterId || "Character"
            color: "white"; font.pixelSize: 11; elide: Text.ElideRight
        }
        Text {
            anchors.right: parent.right; anchors.rightMargin: 7; anchors.bottom: parent.bottom; anchors.bottomMargin: 6
            text: "♥ " + (root.character.hp === undefined ? 0 : root.character.hp)
            color: "#ff8b8b"; font.bold: true
        }
        MouseArea {
            anchors.fill: parent
            enabled: root.selectable && !root.character.defeated
            cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
            onDoubleClicked: root.switchRequested()
        }
    }

    ElementBurst { id: elementalBurst; anchors.centerIn: parent; z: 5 }

    SequentialAnimation {
        id: attackAnimation
        ParallelAnimation {
            NumberAnimation { target: root; property: "y"; to: root.opponent ? 35 : -35; duration: root.attackStyle() === "bow" ? 120 : 180; easing.type: Easing.OutQuad }
            NumberAnimation { target: root; property: "scale"; to: root.attackStyle() === "catalyst" ? 1.18 : 1.08; duration: 160 }
            NumberAnimation { target: root; property: "rotation"; to: root.attackStyle() === "claymore" ? 9 : (root.attackStyle() === "sword" ? -6 : 0); duration: 160 }
        }
        PauseAnimation { duration: root.attackStyle() === "bow" ? 170 : 80 }
        ParallelAnimation {
            NumberAnimation { target: root; property: "y"; to: 0; duration: 260; easing.type: Easing.OutBack }
            NumberAnimation { target: root; property: "scale"; to: 1; duration: 240 }
            NumberAnimation { target: root; property: "rotation"; to: 0; duration: 220 }
        }
    }
}
