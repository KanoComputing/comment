/**
 * SplashScreen.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Kano.Fonts 1.0 as KanoFonts

import Colours 1.0 as Colours


Component {
    id: root

    Rectangle {
        id: view

        signal changeScreen(string screenType)

        color: Colours.Palette.gableGreen
        anchors.fill: parent

        KanoFonts.H1 {
            id: loadingMessage
            text: qsTr("<i>Loading Animation with Welcome Audio Track</i>")
            color: "white"

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.fill: parent
        }

        Component.onCompleted: {
            // _load();
        }

        // --- Private Methods ----------------------------------------------------------

        function _load() {
            cxx_app.load();
            _onLoaded();
        }

        function _onLoaded() {
            console.log("SplashScreen: _onLoaded: Called");
            view.changeScreen("ChallengeScreen");
        }
    }
}
