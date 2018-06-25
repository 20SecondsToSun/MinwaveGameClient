#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QScopedPointer>

#include "network/ClientService.h"
#include "network/socketClient/SocketClient.h"
#include "config/ConfigController.h"
#include "core/MainController.h"
#include "core/AppController.h"
#include "core/IService.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<ConnectedAppData>("ConnectedAppData");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QScopedPointer<Logger> logger(new Logger);
    engine.rootContext()->setContextProperty("logger", logger.data());

    QScopedPointer<ConfigController> configController(new ConfigController);
    engine.rootContext()->setContextProperty("configController", configController.data());

   // QScopedPointer<MainController> mainController(new MainController);
   // engine.rootContext()->setContextProperty("mainController", mainController.data());

    QScopedPointer<AppController> appController(new AppController);
    engine.rootContext()->setContextProperty("appController", appController.data());

    // services
   // QScopedPointer<IService> clientService(new ClientService(engine.rootContext()));
   // engine.rootContext()->setContextProperty("clientService", clientService.data());

    // add services
//    mainController.data()->addService(clientService.data());
    appController.data()->setLogger(logger.data());

    // listeners
    QObject::connect(configController.data(), SIGNAL(configServiceReady(Config*)), appController.data(), SLOT(onConfigLoaded(Config*)));
    QObject::connect(configController.data(), SIGNAL(configServiceError()), appController.data(), SLOT(onConfigError()));

    qmlRegisterType<AppController>("com.app", 1, 0, "AppState");


    // qml
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // config load. entry point
    configController.data()->setLoadingMethod(ConfigLoader::CONFIG_LOAD_METHOD::RESOURCE_FILE);
    configController.data()->load();

    return app.exec();
}
