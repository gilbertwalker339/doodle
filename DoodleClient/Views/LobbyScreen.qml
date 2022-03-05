import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: lobbyScreen;

    function sendMessageChat(message) {
        GameManager.sendMessageRequest(txtChatInput.text);
        txtChatInput.text = "";
    }

    Connections {
        target: GameManager;
        function onMessageChatReceived(message) {
            txtChatList.append(message);
        }
    }

    Rectangle {
        anchors.fill: parent;
        color: "#503434";

        Text {
            id: txtTitle;
            anchors {
                top: parent.top;
                topMargin: 30;
                horizontalCenter: parent.horizontalCenter;
            }
            text: "Lobby " + GameManager.lobbyId;
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }

        Rectangle {
            id: backgroundClientList;
            anchors {
                top: txtTitle.bottom;
                topMargin: 30;
                left: parent.left;
                leftMargin: 30;
            }
            width: 400;
            height: 430;
            radius: 10;
            color: "#C4C4C4";

            ListView {
                id: lvClientList;
                anchors {
                    fill: parent;
                }
                model: GameManager.clientIdInLobby;
                delegate: Text {
                    id: txtUserId;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    font {
                        bold: true;
                        pixelSize: 36;
                    }
                    text: modelData;

                    Image {
                        id: readyImage;
                        visible: false;
                        Connections {
                            target: GameManager;
                            function onUpdateClientReady(clientIdList) {
                                for(var clientId of clientIdList) {
                                    if(clientId === modelData) {
                                        readyImage.visible = true;
                                        break;
                                    }
                                }
                            }
                        }

                        anchors {
                            left: txtUserId.right;
                            leftMargin: 15;
                            verticalCenter: parent.verticalCenter;
                        }

                        width: 50;
                        height: 50;
                        source: "assets/images/check.jpg";
                        fillMode: Image.PreserveAspectFit;
                    }
                }
            }
        }

        Rectangle {
            id: backgroundChatList;
            anchors {
                top: backgroundClientList.top;
                bottom: backgroundClientList.bottom;
                left: backgroundClientList.right;
                leftMargin: 30;
                right: parent.right;
                rightMargin: 30;
            }
            radius: 10;
            color: "#C4C4C4";

            TextEdit {
                id: txtChatList;
                anchors {
                    fill: parent;
                    margins: 20;
                }
                font {
                    bold: true;
                    pixelSize: 24;
                }
                color: "black";
                readOnly: true;
            }
        }

        Rectangle {
            id: backgroundChatInput;
            anchors {
                top: btnSend.top;
                bottom: btnSend.bottom;
                left: backgroundChatList.left;
                right: btnSend.left;
                rightMargin: 30;
            }
            radius: 10;
            color: "#C4C4C4";

            TextInput {
                id: txtChatInput;
                anchors {
                    fill: parent;
                    leftMargin: 10;
                    rightMargin: 10;
                }
                verticalAlignment: Text.AlignVCenter
                color: "white";
                font {
                    bold: true;
                    pixelSize: 36;
                }
                selectByMouse: true;
                clip: true;
                onAccepted: {
                    sendMessageChat(txtChatInput.text);
                }
            }
        }


        Components.GameButton {
            id: btnReady;
            anchors {
                bottom: parent.bottom;
                bottomMargin: 50;
                left: backgroundClientList.left;
            }
            buttonWidth: 230;
            buttonHeight: 70;
            buttonText: "Ready";
            buttonTextSize: 48;
            onButtonClicked: {
                GameManager.readyRequest();
            }
        }

        Components.GameButton {
            id: btnSend;
            anchors {
                bottom: parent.bottom;
                bottomMargin: 50;
                right: backgroundChatList.right;
            }
            buttonWidth: 230;
            buttonHeight: 70;
            buttonText: "Send";
            buttonTextSize: 48;
            onButtonClicked: {
                sendMessageChat(txtChatInput.text);
            }
        }

    }
}
