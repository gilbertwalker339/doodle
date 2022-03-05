import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: gameOverScreen;

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
            text: "Player " + GameManager.bestClientId + " was the best";
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

            Image {
                anchors.fill: parent;
                fillMode: Image.PreserveAspectFit;
                source: "file://" + GameManager.bestImagePath();
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
                Qt.quit();
            }
        }

    }
}
