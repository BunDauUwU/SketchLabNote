import QtQuick
import QtQuick.Layouts
import "../controls"
import lumieTcg

GamePanel {
    id: root

    property string weatherName: "Rain"
    property string description: "Hydro reactions will be easier to enable."
    property int remainingRounds: 2

    implicitWidth: 420
    implicitHeight: 96
    radiusSize: Radius.lg
    highlighted: true

    RowLayout {
        anchors.fill: parent
        anchors.margins: Spacing.md
        spacing: Spacing.md

        Rectangle {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            radius: Radius.pill
            color: Qt.rgba(Theme.primary.r, Theme.primary.g, Theme.primary.b, 0.18)
            border.width: 1
            border.color: Theme.primary

            GameText {
                anchors.centerIn: parent
                text: ({
                        Rain: "☔",
                        Snow: "❄",
                        Thunderstorm: "⚡",
                        Sandstorm: "🌪",
                        Cataclysm: "☄",
                        BurningField: "🔥",
                        Tornado: "🌪"
                    })[root.weatherName] || "☀"
                type: GameText.Body
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: Spacing.xxs

            GameText {
                text: root.weatherName
                type: GameText.Body
                color: Theme.primary
                Layout.fillWidth: true
            }

            GameText {
                text: root.description
                type: GameText.Caption
                color: Theme.textGray
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }

        GameText {
            visible: root.width >= 360
            text: root.remainingRounds + " rounds left"
            type: GameText.Body
            color: Theme.text
        }
    }
}
