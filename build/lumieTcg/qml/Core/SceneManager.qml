import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

    anchors.fill: parent

    StackView {

        id: stack

        anchors.fill: parent

        initialItem: authManager.isAuthenticated ? "../Screens/MainMenu.qml" : "../Screens/SplashScreen.qml"

    }

}