QT += quick websockets

SOURCES += \
        main.cpp \
        Controllers/clientsockethandler.cpp \
        Controllers/gamemanager.cpp \
        Controllers/messagehandler.cpp \

resources.files = \
        main.qml \
        Views/Components/GameButton.qml \
        Views/GameOverScreen.qml \
        Views/HomeScreen.qml \
        Views/JoinScreen.qml \
        Views/LobbyScreen.qml \
        Views/ScribbleScreen.qml \
        Views/SelectScreen.qml \
        Views/TakeawayScreen.qml \
        Views/VoteScreen.qml \
        Views/WaitingScreen.qml \
        Views/assets/images/check.jpg \

resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Controllers/clientsockethandler.h \
    Controllers/gamemanager.h \
    Controllers/messagehandler.h

DISTFILES += \
    Views/Components/GameButton.qml \
    Views/GameOverScreen.qml \
    Views/HomeScreen.qml \
    Views/JoinScreen.qml \
    Views/LobbyScreen.qml \
    Views/ScribbleScreen.qml \
    Views/SelectScreen.qml \
    Views/TakeawayScreen.qml \
    Views/VoteScreen.qml \
    Views/WaitingScreen.qml \
    Views/assets/images/check.jpg \
