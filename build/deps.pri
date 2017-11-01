# deps.pri
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: description


INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/App.h \
    # TODO: Move everything below to Kano QT Sdk repo
    $$PWD/../include/Singleton.h \
    $$PWD/../include/MultiAppInstanceGuard.h \
    $$PWD/../include/X11Input.h
