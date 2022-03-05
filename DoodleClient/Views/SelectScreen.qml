import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: selectScreen;

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
            id: btnCreate;
            anchors {
                top: txtTitle.bottom;
                topMargin: 70;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Create";
            buttonTextSize: 72;
            onButtonClicked: {
                GameManager.createGameRequest();
            }
        }

        Components.GameButton {
            id: btnJoin;
            anchors {
                top: btnCreate.bottom;
                topMargin: 50;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Join";
            buttonTextSize: 72;
            onButtonClicked: {
                mainLoader.source = "Views/JoinScreen.qml";
            }
        }

        Components.GameButton {
            id: btnBack;
            anchors {
                top: btnJoin.bottom;
                topMargin: 50;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Back";
            buttonTextSize: 72;
            onButtonClicked: {
                mainLoader.source = "Views/HomeScreen.qml";
            }
        }

    }
}
