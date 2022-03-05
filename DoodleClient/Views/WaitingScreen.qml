import QtQuick
import QtQuick.Controls
import "Components" as Components

Item {
    id: waitingScreen;

    Rectangle {
        anchors.fill: parent;
        color: "#503434";

        Text {
            id: txtTitle;
            anchors {
                top: parent.top;
                topMargin: 80;
                horizontalCenter: parent.horizontalCenter;
                verticalCenter: parent.verticalCenter;
            }
            text: "Wating for other players<br />to finish...";
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignHCenter;
            font {
                pixelSize: 72;
                bold: true;
            }
            color: "white";
        }
    }
}
