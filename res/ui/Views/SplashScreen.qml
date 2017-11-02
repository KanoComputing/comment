/**
 * SplashScreen.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

import Kano.Fonts 1.0 as KanoFonts

import Colours 1.0 as Colours


Component {
    id: root

    Rectangle {
        id: view
        color: Colours.Palette.backgroundColour;
        anchors.fill: parent

        Component.onCompleted: {
            cxx_app.load();
            console.log(cxx_challengeManager.completedChallenges);
            console.log(cxx_challengeManager.totalChallenges);
        }

        KanoFonts.H2 {
            id: loadingMessage
            text: qsTr("Loading Animation\nwith Welcome Audio Track")
            horizontalAlignment: Text.AlignHCenter

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
