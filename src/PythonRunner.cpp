/**
 * PythonRunner.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QStringList>

#include "PythonRunner.h"
#include "Utils.h"


PythonRunner::PythonRunner(QObject* parent): QObject(parent) {
    m_commandProcess.setProcessChannelMode(QProcess::SeparateChannels);

    QObject::connect(
        &m_commandProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(onCommandProcessFinished(int, QProcess::ExitStatus))
    );
}


PythonRunner::~PythonRunner() {

}


// --- Public Methods -------------------------------------------------------------------


void PythonRunner::load() {
    QDir *p_scriptsDir = findScriptsDir();
    if (p_scriptsDir == NULL) {
        #ifdef QT_DEBUG
            qDebug() << "ERROR: PythonRunner: load: res/scripts dir was not found!";
        #endif
        return;
    }

    QString commandsPreamblePath = p_scriptsDir->absoluteFilePath("_commands_preamble.py");
    QString commandsPostamblePath = p_scriptsDir->absoluteFilePath("_commands_postamble.py");

    delete p_scriptsDir;

    m_commandPreamble = readCommandScript(commandsPreamblePath);
    m_commandPostamble = readCommandScript(commandsPostamblePath);

    #ifdef QT_DEBUG
        qDebug() << "PythonRunner: load:"
                 << "\n\t commandsPreamblePath is" << commandsPreamblePath
                 << "\n\t commandsPostamblePath is" << commandsPostamblePath
                 << "\n\t m_commandPreamble is" << m_commandPreamble
                 << "\n\t m_commandPostamble is" << m_commandPostamble;
    #endif
}


void PythonRunner::executeCommand(QString command) {
    command = command.replace("'", "\'");
    command = command.replace('"', "'");

    QString process = QString("/usr/bin/python -c \"%1%2;%3\"").arg(
        m_commandPreamble, command, m_commandPostamble
    );

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


// --- Private Slot Methods -------------------------------------------------------------


void PythonRunner::onCommandProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    bool successful = (exitCode == 0);
    m_output = m_commandProcess.readAllStandardOutput();
    m_error = m_commandProcess.readAllStandardError();

    #ifdef QT_DEBUG
        qDebug() << "PythonRunner: onCommandProcessFinished:"
                 << "\n\t successful is" << successful
                 << "\n\t exitStatus is" << exitStatus
                 << "\n\t m_output is" << m_output
                 << "\n\t m_error is" << m_error;
    #endif

    emit commandFinished(successful);
}


// --- Private Methods ------------------------------------------------------------------


QDir* PythonRunner::findScriptsDir() {
    QDir *p_scriptsDir = new QDir();
    p_scriptsDir->setNameFilters(QStringList() << "*.py");

    QStringList scriptsDirPaths = {
        // Kano OS install path.
        "/usr/share/comment/scripts",

        #ifdef QT_DEBUG
            // Mac OS local path from executable.
            Utils::getAppRelativePath("../../../../res/scripts"),
            // Raspberry Pi local path from executable.
            Utils::getAppRelativePath("../res/scripts")
        #endif
    };

    for (auto path : scriptsDirPaths) {
        p_scriptsDir->setPath(path);
        if (!p_scriptsDir->entryList().isEmpty()) {
            #ifdef QT_DEBUG
                qDebug() << "PythonRunner: findScriptsDir: Found scripts at" << p_scriptsDir->path();
            #endif
            return p_scriptsDir;
        }
    }
    return NULL;
}


QString PythonRunner::readCommandScript(QString path) {
    QString script("");
    QString line;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        #ifdef QT_DEBUG
            qDebug() << "ERROR: PythonRunner: readCommandScript: Could not open" << path;
        #endif
        return script;
    }

    while (!file.atEnd()) {
        line = file.readLine();

        // Ignore Python comment and empty lines.
        if (line.at(0) == '#' || line == "")
            continue;

        // Remove leading and trailing whitespaces.
        script = script + line.trimmed();
    }

    return script;
}
