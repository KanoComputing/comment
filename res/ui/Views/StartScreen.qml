/**
 * StartScreen.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Kano.Fonts 1.0 as KanoFonts

import Views 1.0 as Views
import Widgets 1.0 as Widgets
import Colours 1.0 as Colours


Component {
    id: root

    Rectangle {
        id: view
        color: Colours.Palette.gableGreen
        anchors.fill: parent

        Rectangle {
            id: appName
            color: "transparent"
            height: Math.round(parent.height * 0.65)

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right

            KanoFonts.H1 {
                id: appNameText
                text: qsTr("Make Me Talk")
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: toStart
            color: "transparent"

            anchors.left: parent.left
            anchors.top: appName.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            KanoFonts.H2 {
                id: toStartText
                text: qsTr(
                    "<font color='%1'><b>Press [ENTER] to Start</b></font>"
                ).arg(Colours.Palette.atlantis)

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
