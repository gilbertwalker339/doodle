import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: voteScreen;

    property string imagePathVote: "";

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
            text: "Vote for the best image!";
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }

        GridView {
            anchors {
                top: txtTitle.bottom;
                topMargin: 80;
                left: parent.left;
                leftMargin: 30;
                right: parent.right;
                rightMargin: 30;
            }
            height: 450;
            cellWidth: 585;
            cellHeight: 210;
            clip: true;
            model: GameManager.imagePathList;
            delegate: Rectangle {
                color: "#C4C4C4";
                width: 575;
                height: 200;
                border {
                    width: modelData == imagePathVote ? 5 : 0;
                    color: "red";
                }

                Image {
                    anchors.fill: parent;
                    fillMode: Image.PreserveAspectFit;
                    source: "file://" + modelData;
                }

                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        imagePathVote = modelData;
                    }
                }
            }
        }

        Components.GameButton {
            id: btnVote;
            anchors {
                bottom: parent.bottom;
                bottomMargin: 10;
                right: parent.right;
                rightMargin: 50;
            }
            buttonWidth: 250;
            buttonHeight: 80;
            buttonText: "Vote";
            buttonTextSize: 48;
            buttonColor: "#147630";
            onButtonClicked: {
                GameManager.voteRequest(imagePathVote);
                mainLoader.source = "Views/WaitingScreen.qml";
            }
        }

    }
}
