/**
 * InputRunner.h
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * Header for the InputRunner class.
 */


#ifndef __INPUT_RUNNER_H__
#define __INPUT_RUNNER_H__


#include <QObject>
#include <QString>

#include "PythonRunner.h"


class InputRunner: public PythonRunner
{
    Q_OBJECT

    public:
        InputRunner(QObject* parent = 0);
        ~InputRunner();

    signals:
        void requestHelp();
        void requestList();
        void requestQuit();

    public:
        Q_INVOKABLE bool isValid(QString validate, QString userInput);
};


#endif
