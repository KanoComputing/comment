/**
 * Step.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3


Item {
    id: root

    property string copy: "copy property not set!"
    property string hint: ""
    property string validate: ""

    signal completed()


    function initialise() {

    }

    function reset() {
        copy = "copy property not set!";
        hint = ""
        validate = ""
    }
}
