/**
 * InputRunner.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include <QDebug>
#include <QObject>
#include <QString>

#include "InputRunner.h"
#include "PythonRunner.h"


InputRunner::InputRunner(QObject* parent): QObject(parent) {

}


InputRunner::~InputRunner() {

}


// --- Public QML Invokable Methods -----------------------------------------------------


Q_INVOKABLE bool InputRunner::checkInstruction(QString userInput) {
    if (userInput == "help") {
        emit requestHelp();
        #ifdef QT_DEBUG
            qDebug() << "InputRunner: checkInstruction: 'help' instrunction";
        #endif
        return true;

    } else if (userInput == "list") {
        emit requestList();
        #ifdef QT_DEBUG
            qDebug() << "InputRunner: checkInstruction: 'list' instruction";
        #endif
        return true;

    } else if (userInput == "exit") {
        emit requestQuit();
        #ifdef QT_DEBUG
            qDebug() << "InputRunner: checkInstruction: 'exit' instruction";
        #endif
        return true;
    }
    #ifdef QT_DEBUG
        qDebug() << "InputRunner: checkInstruction: No instruction";
    #endif
    return false;
}


Q_INVOKABLE bool InputRunner::isValid(QString userInput, QString validate) {
    // TODO: Support regular expressions.
    bool valid = (validate != "" && userInput == validate);

    #ifdef QT_DEBUG
        qDebug() << "InputRunner: isValid:"
                 << "\n\t userInput is" << userInput
                 << "\n\t validate is" << validate
                 << "\n\t valid is" << valid;
    #endif
    return valid;
}


Q_INVOKABLE void InputRunner::execute(QString userInput) {
    m_runner.executeCommand(userInput);
}


Q_INVOKABLE QString InputRunner::getOutput() const {
    return m_runner.getOutput();
}


Q_INVOKABLE QString InputRunner::getError() const {
    return m_runner.getError();
}


// --- Private Methods ------------------------------------------------------------------


void InputRunner::onCommandFinished(bool successful) {
    emit executeFinished(successful);
}
