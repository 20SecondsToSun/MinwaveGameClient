QT += qml quick charts widgets

CONFIG += c++11

SOURCES += main.cpp \
    config/Config.cpp \
    config/ConfigController.cpp \
    config/ConfigLoader.cpp \
    config/ConfigParser.cpp \
    config/ConfigWriter.cpp \
    core/IService.cpp \
    core/MainController.cpp \
    core/Types.cpp \
    network/socketClient/SocketClient.cpp \
    network/socketClient/TCPSocketClient.cpp \
    network/socketClient/TCPSocketClientCmnd.cpp \
    tools/Logger.cpp \
    network/ClientService.cpp \
    network/http/HTTPClient.cpp \
    mindwave/MindWave.cpp \
    mindwave/GameTaskManager.cpp \
    mindwave/VelocityCalculator.cpp \
    tools/MathTools.cpp \
    mindwave/TaskCreator.cpp \
    mindwave/GameTask.cpp \
    mindwave/GamePreTask.cpp \
    mindwave/GameSession.cpp \
    mindwave/GamePostTask.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config/Config.h \
    config/ConfigController.h \
    config/ConfigLoader.h \
    config/ConfigParser.h \
    config/ConfigWriter.h \
    core/IService.h \
    core/MainController.h \
    core/Types.h \
    network/socketClient/SocketClient.h \
    network/socketClient/TCPSocketClient.h \
    network/socketClient/TCPSocketClientCmnd.h \
    tools/Logger.h \
    network/ClientService.h \
    network/http/HTTPClient.h \
    mindwave/MindWave.h \
    mindwave/GameTask.h \
    mindwave/GameTaskManager.h \
    mindwave/VelocityCalculator.h \
    tools/MathTools.h \
    mindwave/TaskCreator.h \
    mindwave/GamePreTask.h \
    mindwave/GameSession.h \
    mindwave/gametypes.h \
    mindwave/GamePostTask.h

DISTFILES +=
