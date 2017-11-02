/**
 * Utils.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QString>

#include "Utils.h"


void Utils::runCmd(QString cmd) {
    #ifdef __arm__  // TODO: This should be an RPI flag.
        #ifdef QT_DEBUG
            qDebug() << "Utils: runCmd: cmd is" << cmd;
        #endif
        system(cmd.toStdString().c_str());

    #elif defined QT_DEBUG
        qDebug() << "Utils: runCmd: Not executing" << cmd << "on this platform!";
    #endif
}


QString Utils::getAppRelativePath(QString path) {
    return QDir::cleanPath(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(path));
}
