/**
 * Main.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * The entry point into code base.
 * The main function sets up the application, runs it, and exits with its return code.
 *
 * An RPi workaround (X11 input) is also implemented here which is a fix for having
 * both the X11 mouse and the Qt mouse at the same time and keyboard input reaching
 * X11 apps behind it.
 */


#include <QDebug>

#include "X11Input.h"
#include "MultiAppInstanceGuard.h"

#include "App.h"


int main(int argc, char *argv[]) {

    // This app does not allow multiple instances.
    // MultiAppInstanceGuard guard;
    // if (!guard.run())
    //     return 100;

    // Initialise the X11 input grabbing singleton.
    X11Input::getInstance().initialise();

    // Capture X11 input from propagating behind the Qt app and hide X11 cursor.
    X11Input::getInstance().capture();

    // Create the app to be run and pass the arguments.
    App app(argc, argv);
    int rc = app.exec();

    // Preform an app clean up.
    X11Input::getInstance().restore();
    X11Input::getInstance().clean();

    // Exit with the app return code.
    #ifdef QT_DEBUG
        qDebug() << "main: rc is" << rc;
    #endif
    return rc;
}
