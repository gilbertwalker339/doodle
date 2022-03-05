import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: homeScreen;

    Rectangle {
        anchors.fill: parent;
        color: "#503434";

        Text {
            id: txtTitle;
            anchors {
                top: parent.top;
                topMargin: 80;
                horizontalCenter: parent.horizontalCenter;
            }
            text: "Doodle Drawer";
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }

        Components.GameButton {
            id: btnPlay;
            anchors {
                top: txtTitle.bottom;
                topMargin: 150;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Play";
            buttonTextSize: 72;
            onButtonClicked: {
                mainLoader.source = "Views/SelectScreen.qml";
            }
        }

        Components.GameButton {
            id: btnQuit;
            anchors {
                top: btnPlay.bottom;
                topMargin: 50;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Quit";
            buttonTextSize: 72;
            onButtonClicked: {
                Qt.quit();
            }
        }

    }
}
