/**
 * Challenge.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Controllers 1.0


Item {
    id: root

    property string name: "name property not set!"
    property int index: 0
    property list<Step> steps

    property int currentStep: 0
    property bool isCompleted: false
    property int totalSteps: steps.length

    signal completed()


    function initialise() {

    }

    function reset() {
        name = "name property not set!";
        index = 0;
        steps = [];
        currentStep = 0;
        totalSteps = 0;
    }
}
