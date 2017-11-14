/**
 * Utils.h
 *
 * Copyright (C) 2016 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO
 */


#ifndef __UTILS_H__
#define __UTILS_H__


#include <QDir>
#include <QString>


class Utils {

    public:
        static void runCmd(QString cmd);
        static QString getAppRelativePath(QString path);

    private:
        Utils() {}
};


#endif
