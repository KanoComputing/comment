/**
 * Main.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * The application window contains a top bar and the ShutdownMenu view.
 *
 * Note that the strange Item wrapper is designed to work as the actual application
 * window container because on the RPi it is running under eglfs. Therefore, the
 * workaround is to always run the app in Fullscreen mode with a transparent background
 * and wrap the actual components into a "window".
 *
 * TODO: template this for reusability
 */


import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

import Views 1.0 as Views


ApplicationWindow {
    id: root
    width: Screen.width
    height: Screen.height
    flags: Qt.FramelessWindowHint
    visible: true
    visibility: "FullScreen"
    color: "transparent"

    // Application Window wrapper workaround.
    Item {
        id: window
        width: root.width
        height: root.height
        anchors.centerIn: parent

        // The initial Loading view.
        Views.SplashScreen {
            id: splashScreen
        }

        Views.StartScreen {
            id: startScreen
        }

        Views.ChallengeScreen {
            id: challengeScreen
        }

        Views.ChallengeSelectionScreen {
            id: challengeSelectionScreen
        }

        Views.HelpScreen {
            id: helpScreen
        }

        Loader {
            id: viewLoader
            sourceComponent: challengeScreen

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
