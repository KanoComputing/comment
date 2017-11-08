/**
 * PythonRunner.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QString>

#include "PythonRunner.h"


PythonRunner::PythonRunner(QObject* parent): QObject(parent) {
    m_commandProcess.setProcessChannelMode(QProcess::SeparateChannels);

    QObject::connect(
        &m_commandProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(onCommandProcessFinished(int, QProcess::ExitStatus))
    );
    QObject::connect(
        &m_commandProcess, SIGNAL(stateChanged(QProcess::ProcessState)),
        this, SLOT(onCommandProcessStateChanged(QProcess::ProcessState))
    );
}


PythonRunner::~PythonRunner() {

}


// --- Public Methods -------------------------------------------------------------------


void PythonRunner::executeCommand(QString command) {
    QString header(
        "from os.path import abspath, join, dirname ; "
        "import sys ; "
        // "import json ; "
        "sys.path.append(abspath(join(dirname('.'), 'libs'))) ; "
        // "print json.dumps(sys.path, indent=4) ; "
        "from pycomment.functions import say ; "
    );

    command = command.replace('"', "'");
    QString process = QString("/usr/bin/python -c \"%1 %2\"").arg(header, command);

    #ifdef QT_DEBUG
        qDebug() << "PythonRunner: executeCommand: process is" << process;
    #endif

    m_commandProcess.start(process);
}


QString PythonRunner::getOutput() const {
    return m_output;
}


QString PythonRunner::getError() const {
    return m_error;
}


// --- Private Methods ------------------------------------------------------------------


void PythonRunner::onCommandProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    bool successful = (exitStatus == QProcess::NormalExit);
    m_output = m_commandProcess.readAllStandardOutput();
    m_error = m_commandProcess.readAllStandardError();

    #ifdef QT_DEBUG
        qDebug() << "PythonRunner: onCommandProcessFinished:"
                 << "\n\t successful is" << successful
                 << "\n\t m_output is" << m_output
                 << "\n\t m_error is" << m_error;
    #endif
    // emit commandFinished(successful);
}


void PythonRunner::onCommandProcessStateChanged(QProcess::ProcessState newState) {
    #ifdef QT_DEBUG
        qDebug() << "PythonRunner: onCommandProcessStateChanged: newState is" << newState;
    #endif
}
