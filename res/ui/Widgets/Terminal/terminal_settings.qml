/**
 * terminal_settings.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPLv2
 *
 * Settings for the terminal widget
 *
 */


pragma Singleton

import QtQuick 2.0

import Colours 1.0 as Colours


QtObject {
    property color bg_color: 'black'
    property string bg_source: ''
    property color fg_color: 'white'
    property var font_family: 'FreeMono'
    property var font_weight: Font.Normal
    property string prompt_marker: '<font color="%1">></font>'.arg(Colours.Palette.blueTextColour);
    property int font_size: 24
    property int margins: 100
}
