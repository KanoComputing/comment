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
    color: Colours.Palette.regentGray

    KanoFonts.H4 {
        id: loadingMessage
        color: Colours.Palette.gableGreen
        verticalAlignment: Text.AlignVCenter

        text: qsTr(
            "Type \"<font color='%1'>help</font>\" for commands, " +
                 "\"<font color='%1'>list</font>\" for challenges, " +
                 "\"<font color='%1'>exit</font>\" to quit"
        ).arg(Colours.Palette.atlantis)

        anchors.fill: parent
        anchors.leftMargin: 10

        Component.onCompleted: {
            console.log(text);
        }
    }
}
