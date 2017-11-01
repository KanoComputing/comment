/**
 * Challenge.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


Component {
    id: root

    readonly property string name
    readonly property string index
    readonly property int steps

    readonly property int currentStep
    readonly property int totalSteps

    signal challengeCompleted()


    function initialise() {

    }

    function reset() {
        name = 'name property not set!';
        index = 0;
        steps = [];
        currentStep = 0;
        totalSteps = 0;
    }
}
