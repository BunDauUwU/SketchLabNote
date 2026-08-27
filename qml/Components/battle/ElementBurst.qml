import QtQuick

Item {
    id: root
    width: 190; height: 190
    property color effectColor: "#ffffff"

    function colorFor(element) {
        const key = String(element).toLowerCase()
        if (key.indexOf("pyro") >= 0) return "#ff6b3d"
        if (key.indexOf("hydro") >= 0) return "#51a9ff"
        if (key.indexOf("cryo") >= 0) return "#9cecff"
        if (key.indexOf("electro") >= 0) return "#ba7cff"
        if (key.indexOf("dendro") >= 0) return "#8dcc4b"
        if (key.indexOf("anemo") >= 0) return "#64e0ba"
        if (key.indexOf("geo") >= 0) return "#e8b74d"
        return "#e9edf2"
    }
    function play(element) { effectColor = colorFor(element); burst.restart() }

    Rectangle { id: ring; anchors.centerIn: parent; width: 72; height: 72; radius: 36; color: "transparent"; border.width: 8; border.color: root.effectColor; opacity: 0 }
    Rectangle { id: core; anchors.centerIn: parent; width: 48; height: 48; radius: 24; color: root.effectColor; opacity: 0 }
    Text { id: glyph; anchors.centerIn: parent; text: "✦"; color: "white"; font.pixelSize: 38; opacity: 0 }

    ParallelAnimation {
        id: burst
        NumberAnimation { target: ring; property: "scale"; from: 0.25; to: 2.3; duration: 560; easing.type: Easing.OutCubic }
        SequentialAnimation { PropertyAction { target: ring; property: "opacity"; value: 0.9 }; NumberAnimation { target: ring; property: "opacity"; to: 0; duration: 560 } }
        NumberAnimation { target: core; property: "scale"; from: 0.2; to: 1.8; duration: 400; easing.type: Easing.OutQuad }
        SequentialAnimation { PropertyAction { target: core; property: "opacity"; value: 0.65 }; NumberAnimation { target: core; property: "opacity"; to: 0; duration: 420 } }
        SequentialAnimation { PropertyAction { target: glyph; property: "opacity"; value: 1 }; NumberAnimation { target: glyph; property: "opacity"; to: 0; duration: 500 } }
    }
}
