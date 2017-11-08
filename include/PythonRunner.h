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


#include <QObject>
#include <QProcess>
#include <QString>


class PythonRunner: public QObject
{
    public:
        PythonRunner(QObject* parent = 0);
        ~PythonRunner();

    signals:
        void commandFinished(bool successful);

    public:
        void executeCommand(QString command);

        QString getOutput() const;
        QString getError() const;

    private:
        QProcess m_commandProcess;
        QString m_output;
        QString m_error;

    private:
        void onCommandProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
        void onCommandProcessStateChanged(QProcess::ProcessState newState);
};


#endif
