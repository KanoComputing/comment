/**
 * App.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * The application coordinator.
 *
 * It instantiates the Args and Window and sets up the QML Engine. The Window is
 * exposed to the QML to interface with.
 */


#include <QGuiApplication>
#include <QQmlApplicationEngine>
// #include <QQmlEngine>
// #include <QJSEngine>
#include <QQmlContext>
#include <QString>
#include <QDir>
#include <QDebug>

#include "App.h"
#include "ChallengeManager.h"
#include "InputRunner.h"


App::App(int &argc, char **argv): QGuiApplication(argc, argv) {

    // Adding include paths to the QML, SDK, and local development paths.
    QStringList includePaths = {
        "/usr/share/comment/ui",
        "/usr/share/kano-qt-sdk",

        #ifdef QT_DEBUG
            // Mac OS local path from executable.
            getAppRelativePath("../../../../res/ui"),
            getAppRelativePath("../../../../../kano-qt-sdk/imports"),
            // Raspberry Pi local path from executable.
            getAppRelativePath("../res/ui"),
            getAppRelativePath("../../kano-qt-sdk/imports")
        #endif
    };

    for (auto path : includePaths) {
        m_engine.addImportPath(path);
        #ifdef QT_DEBUG
            qDebug() << "App: constructor: Adding include path" << path;
        #endif
    }

    // Exposing object references to QML and loading the Main QML.
    m_engine.rootContext()->setContextProperty("cxx_app", this);
    m_engine.rootContext()->setContextProperty("cxx_challengeManager", &m_challengeManager);
    m_engine.rootContext()->setContextProperty("cxx_inputRunner", &m_inputRunner);
    // qmlRegisterType<ChallengeManager>("ChallengeManager", 1, 0, "ChallengeManager");
    // qmlRegisterSingletonType<ChallengeManager>(
    //     "ChallengeManager", 1, 0, "ChallengeManager", this->challengeManagerSingletonTypeProvider
    // );
    m_engine.load(QUrl(QStringLiteral("qrc:/ui/Main.qml")));

    // Setup a quit event handler for the application.
    connect(this, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));
}

App::~App() {

}

// --- Public Invokable Methods ---------------------------------------------------------


Q_INVOKABLE void App::load() {
    #ifdef QT_DEBUG
        qDebug() << "App: load: Called";
    #endif
    m_challengeManager.load(&m_engine);

    emit loaded();
}


// --- Public Methods -------------------------------------------------------------------

// QObject* App::challengeManagerSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
//     // Q_UNUSED(engine)
//     // Q_UNUSED(scriptEngine)

//     ChallengeManager *singleton = new ChallengeManager();
//     return singleton;
// }

// --- Public Slots ---------------------------------------------------------------------

void App::exitApp(int rc) {
    this->exit(rc);
}

// --- Private Slots --------------------------------------------------------------------

void App::aboutToQuit() {
    // QString actionCmd;

    // // Execute all shell commands registered as exit actions in parallel.
    // for(auto const &actionId: m_shellExitActions.keys()) {
    //     actionCmd = m_shellExitActions.value(actionId);
    //     #ifdef QT_DEBUG
    //         qDebug() << "App: aboutToQuit: actionId is" << actionId
    //                  << "actionCmd is" << actionCmd;
    //     #endif
    //     Utils::runCmd(actionCmd);
    // }
}

// --- Private --------------------------------------------------------------------------

QString App::getAppRelativePath(QString path) {
    return QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(path);
}
