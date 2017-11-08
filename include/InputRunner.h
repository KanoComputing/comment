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


class InputRunner: public QObject
{
    Q_OBJECT

    public:
        InputRunner(QObject* parent = 0);
        ~InputRunner();

    signals:
        void requestHelp();
        void requestList();
        void requestQuit();

        void executeFinished(bool successful);

    public:
        Q_INVOKABLE bool checkInstruction(QString userInput);
        Q_INVOKABLE bool isValid(QString userInput, QString validate);

        Q_INVOKABLE void execute(QString userInput);
        Q_INVOKABLE QString getOutput() const;
        Q_INVOKABLE QString getError() const;

    private:
        PythonRunner m_runner;

    private:
        void onCommandFinished(bool successful);
};


#endif
