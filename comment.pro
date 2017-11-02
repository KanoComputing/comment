# comment.pro
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: description


TEMPLATE = app

CONFIG += \
    kano_build_options \
    kano_debug_target

include(build/i18n.pri)
include(build/deps.pri)

SOURCES += \
    $$PWD/src/Main.cpp \
    $$PWD/src/App.cpp \
    $$PWD/src/ChallengeManager.cpp \
    $$PWD/src/Utils.cpp \
    # TODO: Move everything below to Kano QT Sdk repo
    $$PWD/src/MultiAppInstanceGuard.cpp \
    $$PWD/src/X11Input.cpp

RESOURCES += \
    $$PWD/res/all.qrc


# TODO: Move the logic below into kano-qt-sdk and remove!

# Output the binary in the bin/ dir
DESTDIR = bin
# Move the generated i18n folder into the res/ dir
QMAKE_POST_LINK += \
    rm -rf $$PWD/res/i18n && \
    mv $$PWD/i18n $$PWD/res
