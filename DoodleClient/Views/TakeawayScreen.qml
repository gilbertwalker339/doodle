import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: takeawayScreen;

    Component.onCompleted: {
        scribbleCavas.loadImage("file://" + GameManager.scribblePath);
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
            text: GameManager.objectDraw;
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }

        Rectangle {
            id: backgroundCanvas;
            anchors {
                top: txtTitle.bottom;
                topMargin: 30;
                left: parent.left;
                leftMargin: 30;
                right: parent.right;
                rightMargin: 30;
            }
            height: 430;
            radius: 10;
            color: "#C4C4C4";

            Canvas {
                id: scribbleCavas;

                property real startX: -1;
                property real startY: -1;
                property real endX: -1;
                property real endY: -1;

                anchors.fill: parent;
                onPaint: {
                    var ctx = scribbleCavas.getContext("2d");
                    ctx.lineWidth = 5;
                    ctx.strokeStyle = "red";
                    ctx.lineJoin = "round";
                    ctx.beginPath();
                    ctx.moveTo(startX, startY);
                    ctx.lineTo(endX, endY);
                    ctx.closePath();
                    ctx.stroke();
                    startX = endX;
                    startY = endY;
                }
                onImageLoaded: {
                    var ctx = scribbleCavas.getContext("2d");
                    ctx.drawImage(GameManager.scribblePath, 0, 0, scribbleCavas.width, scribbleCavas.height);
                    scribbleCavas.requestPaint();
                }
            }

            MouseArea {
                anchors.fill: parent;
                onPressed: {
                    scribbleCavas.startX = mouseX;
                    scribbleCavas.startY = mouseY;
                }

                onPositionChanged: {
                    scribbleCavas.endX = mouseX;
                    scribbleCavas.endY = mouseY;

                    scribbleCavas.requestPaint();
                }
            }
        }

        Components.GameButton {
            id: btnClear;
            anchors {
                bottom: parent.bottom;
                bottomMargin: 50;
                left: backgroundCanvas.left;
            }
            buttonWidth: 250;
            buttonHeight: 80;
            buttonText: "Clear";
            buttonTextSize: 48;
            buttonColor: "#EA5555";
            onButtonClicked: {

            }
        }

        Components.GameButton {
            id: btnDone;
            anchors {
                bottom: parent.bottom;
                bottomMargin: 50;
                right: backgroundCanvas.right;
            }
            buttonWidth: 250;
            buttonHeight: 80;
            buttonText: "Done";
            buttonTextSize: 48;
            buttonColor: "#147630";
            onButtonClicked: {
                scribbleCavas.save("temp.png");
                GameManager.drawnRequest();
                mainLoader.source = "Views/WaitingScreen.qml";
            }
        }

    }
}
