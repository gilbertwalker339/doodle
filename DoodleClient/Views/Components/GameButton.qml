import QtQuick
import QtQuick.Controls

Rectangle {
    id: gameButton;

    signal buttonClicked();

    property color buttonColor: "#CDAA30";
    property color buttonClickedColor: "#CDAA30";
    property int buttonWidth: 350;
    property int buttonHeight: 100;
    property string buttonText: "";
    property int buttonTextSize: 72;

    width: gameButton.buttonWidth;
    height: gameButton.buttonHeight;
    color: gameButton.buttonColor;
    radius: 10;

    Text {
        text: gameButton.buttonText;
        anchors.centerIn: parent;
        font {
            pixelSize: gameButton.buttonTextSize;
            bold: true;
        }
        color: "white";
    }

    MouseArea {
        anchors.fill: parent;
        onEntered: {
            gameButton.buttonClicked();
            gameButton.color = gameButton.buttonClickedColor;
        }
        onReleased: {
            gameButton.color = gameButton.buttonColor;
        }
    }
}
