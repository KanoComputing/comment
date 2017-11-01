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
#include <QQmlContext>
#include <QString>
#include <QDir>
#include <QDebug>

#include "App.h"


App::App(int &argc, char **argv): QGuiApplication(argc, argv) {

    // Adding include paths to the QML, SDK, and local development paths.
    QStringList includePaths = {
        "/usr/share/comment/ui",
        "/usr/share/kano-qt-sdk",

        #ifdef QT_DEBUG
            getAppRelativePath("../../../../res/ui"),
            getAppRelativePath("../res/ui"),
            getAppRelativePath("../../../../../kano-qt-sdk/imports"),
            getAppRelativePath("../../../kano-qt-sdk/imports")
        #endif
    };

    for (auto path : includePaths)
        m_engine.addImportPath(path);

    // Exposing object references to QML and loading the Main QML.
    // m_engine.rootContext()->setContextProperty("cxx_shutdown", &m_shutdown);
    m_engine.load(QUrl(QStringLiteral("qrc:/ui/Main.qml")));

    // Setup a quit event handler for the application.
    connect(this, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));
}

App::~App() {

}

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

// --- Public Slots ---------------------------------------------------------------------

void App::exitApp(int rc) {
    this->exit(rc);
}

// --- Private --------------------------------------------------------------------------

QString App::getAppRelativePath(QString path) {
    return QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(path);
}
