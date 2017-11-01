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
#include <QQmlApplicationEngine>


class App: public QGuiApplication
{
    Q_OBJECT

    public:
        App(int &argc, char **argv);
        ~App();

    public slots:
        Q_INVOKABLE void exitApp(int rc);

    private:
        QQmlApplicationEngine m_engine;

        QString getAppRelativePath(QString path);

    private slots:
        void aboutToQuit();
};


#endif
