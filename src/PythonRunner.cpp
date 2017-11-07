/**
 * PythonRunner.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include "PythonRunner.h"


PythonRunner::PythonRunner(QObject* parent): QObject(parent) {

}


PythonRunner::~PythonRunner() {

}


// --- Public QML Invokable Methods -----------------------------------------------------


Q_INVOKABLE bool PythonRunner::execute(QString command) {
    return true;
}


Q_INVOKABLE QString PythonRunner::getError() const {
    return "";
}