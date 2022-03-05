import QtQuick
import QtQuick.Controls

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")

    Connections {
        target: GameManager;
        function onCreateGameFinished() {
            mainLoader.source = "Views/LobbyScreen.qml";
        }
        function onReadyLobbyReceived() {
            mainLoader.source = "Views/ScribbleScreen.qml";
        }
        function onNextToTakeway() {
             mainLoader.source = "Views/TakeawayScreen.qml";
        }
        function onNextToVote() {
            mainLoader.source = "Views/VoteScreen.qml";
        }
        function onReadyGameOverReceived(highestClientId) {
            GameManager.bestClientId = highestClientId;
            mainLoader.source = "Views/GameOverScreen.qml";
        }
    }

    Loader {
        id: mainLoader;
        anchors.fill: parent;
        source: "Views/HomeScreen.qml";
    }
}
