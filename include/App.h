/**
 * App.h
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * Header for the App class.
 */


#ifndef __APP_H__
#define __APP_H__


#include <QGuiApplication>
// #include <QQmlEngine>
// #include <QJSEngine>
#include <QQmlApplicationEngine>

#include "ChallengeManager.h"
#include "InputRunner.h"


class App: public QGuiApplication
{
    Q_OBJECT

    public:
        App(int &argc, char **argv);
        ~App();

    // public:
    //     static QObject* challengeManagerSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    signals:
        void loaded();

    public:
        Q_INVOKABLE void load();

    public slots:
        Q_INVOKABLE void exitApp(int rc);

    private:
        QQmlApplicationEngine m_engine;
        ChallengeManager m_challengeManager;
        InputRunner m_inputRunner;

    private:
        QString getAppRelativePath(QString path);

    private slots:
        void aboutToQuit();
};


#endif
