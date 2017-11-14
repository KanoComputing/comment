/**
 * ChallengeScreen.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Views 1.0 as Views
import Widgets 1.0 as Widgets
import Colours 1.0 as Colours


Component {
    id: root

    Rectangle {
        id: view

        signal changeScreen(string screenType)

        color: Colours.Palette.gableGreen
        anchors.fill: parent

        Views.InteractiveIDE {
            id: interactiveIDE
            width: Math.round(view.width * 0.62)

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }

        Widgets.VerticalSeparator {
            id: verticalSeparator
            width: 1
            anchors.top: parent.top
            anchors.left: interactiveIDE.right
            anchors.bottom: parent.bottom
        }

        Views.Avatar {
            id: avatar
            anchors.top: parent.top
            anchors.left: verticalSeparator.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }

        Component.onCompleted: {
            cxx_app.load();
        }
    }
}
