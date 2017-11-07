/**
 * InputRunner.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include "InputRunner.h"


InputRunner::InputRunner(QObject* parent): PythonRunner(parent) {

}


InputRunner::~InputRunner() {

}


// --- Public QML Invokable Methods -----------------------------------------------------


Q_INVOKABLE bool InputRunner::isValid(QString validate, QString userInput) {
    // TODO: WIP
    return (validate == userInput);
}