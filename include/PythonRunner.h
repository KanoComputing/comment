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
#include <QString>


class PythonRunner: public QObject
{
    Q_OBJECT

    public:
        PythonRunner(QObject* parent = 0);
        ~PythonRunner();

    public:
        Q_INVOKABLE bool execute(QString command);
        Q_INVOKABLE QString getError() const;
};


#endif
