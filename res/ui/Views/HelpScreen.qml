/**
 * HelpScreen.qml
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
            id: helpBanner
            color: "transparent"
            height: Math.round(parent.height * 0.3)

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.leftMargin: Math.round(view.width * 0.1)
            anchors.rightMargin: anchors.leftMargin

            KanoFonts.H1 {
                id: helpBannerText
                text: qsTr("Help")
                color: "white"

                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: selectChallenge
            color: "transparent"

            anchors.left: parent.left
            anchors.top: helpBanner.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: Math.round(view.width * 0.1)
            anchors.rightMargin: anchors.leftMargin

            KanoFonts.H2 {
                id: selectChallengeText
                text: qsTr(
                    "<b>Coding is fun! I am here to help.\n" +
                    "Type a <font color='%1'>Number</font> to learn more about a" +
                    " coding topic.</b>"
                ).arg(Colours.Palette.swampGreen)
                color: "white"
            }
        }
    }
}
