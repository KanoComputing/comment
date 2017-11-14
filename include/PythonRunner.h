/**
 * PythonRunner.h
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * Header for the PythonRunner class.
 */


#ifndef __PYTHON_RUNNER_H__
#define __PYTHON_RUNNER_H__


#include <QDir>
#include <QObject>
#include <QProcess>
#include <QString>


class PythonRunner: public QObject
{
    Q_OBJECT

    public:
        PythonRunner(QObject* parent = 0);
        ~PythonRunner();

    public:
        void load();

        void executeCommand(QString command);

        QString getOutput() const;
        QString getError() const;

    signals:
        void commandFinished(bool successful);

    private:
        QProcess m_commandProcess;
        QString m_output;
        QString m_error;

        QString m_commandPreamble;
        QString m_commandPostamble;

    private slots:
        void onCommandProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    private:
        QDir* findScriptsDir();
        QString readCommandScript(QString path);
};


#endif
