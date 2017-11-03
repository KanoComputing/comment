/**
 * IdeFooter.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Kano.Fonts 1.0 as KanoFonts

import Colours 1.0 as Colours


Rectangle {
    id: root
    color: Colours.Palette.ideFooterColour

    KanoFonts.H4 {
        id: loadingMessage
        color: Colours.Palette.backgroundColour
        text: qsTr("Type \"help\" for commands, \"list\" for challenges, \"exit\" to quit")
        verticalAlignment: Text.AlignVCenter

        anchors.fill: parent
        anchors.leftMargin: 10
    }
}
