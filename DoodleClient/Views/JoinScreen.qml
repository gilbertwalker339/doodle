import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: joinScreen;

    Connections {
        target: GameManager;
        function onFailedLobby() {
            popup.open();
        }
    }

    Popup {
        id: popup;
        anchors.centerIn: parent;
        width: 600;
        height: 300;
        modal: true;
        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape;
        Text {
            anchors.centerIn: parent;
            text: "Lobby is not exists!";
            font {
                bold: true;
                pixelSize: 36;
            }
        }
    }

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
            text: "Enter lobby code";
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }

        Rectangle {
            id: backgroundLobbyCode;
            anchors {
                top: txtTitle.bottom;
                topMargin: 60;
                horizontalCenter: parent.horizontalCenter;
            }
            width: 500;
            height: 100;
            radius: 10;
            color:"#C4C4C4";

            TextInput {
                id: txtLobbyCode;
                anchors {
                    fill: parent;
                }
                font {
                    bold: true;
                    pixelSize: 48;
                }
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
                color: "black";
                inputMask: "9999";
                maximumLength: 4;
            }
        }

        Components.GameButton {
            id: btnJoin;
            anchors {
                top: backgroundLobbyCode.bottom;
                topMargin: 80;
                horizontalCenter: parent.horizontalCenter;
            }

            buttonWidth: 350;
            buttonHeight: 100;
            buttonText: "Join";
            buttonTextSize: 72;
            onButtonClicked: GameManager.joinGameRequest(txtLobbyCode.text);
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
                mainLoader.source = "Views/SelectScreen.qml";
            }
        }

    }
}
