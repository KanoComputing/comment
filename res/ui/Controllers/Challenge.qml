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
import Colours 1.0 as Colours


Item {
    id: root

    property string name: qsTr("Challenge '%1'").arg(index)
    property int index: 0
    property list<Step> steps
    property bool hasPlayground: false
    property int playgroundPlays: 3
    property string nextChallengeHint: qsTr(
        "Nice coding! Shall we start the next challenge?\n" +
        "Type <font color='%1'><b>yes</b></font> or <font color='%1'><b>no</b></font>"
    ).arg(Colours.Palette.atlantis)

    property int currentStepIndex: 0
    property Step currentStep: steps[currentStepIndex]
    property bool isCompleted: false
    property int totalSteps: steps.length

    signal completed(string challengeId, int challengeIndex)

    signal requestPrintText(string text)
    signal requestClear()
    signal requestNewStepConnections()
    signal requestOldStepDisconnect()


    onCurrentStepChanged: {
        console.log("Challenge: onCurrentStepChanged: Called");
        _runCurrentStep();
    }

    // --- Public Slot Methods ----------------------------------------------------------

    function start() {
        console.log("Challenge: start: Starting first step");
        requestClear();
        requestPrintText(name);
        _runCurrentStep();
    }

    function run() {
        console.log("Challenge: run: Called");

        if (currentStepIndex + 1 >= steps.length) {
            console.log("Challenge: run: Challenge completed");
            completed(objectName, index);
            cxx_challengeManager.nextChallenge();
            return;
        }
        requestOldStepDisconnect();
        currentStep.completed.disconnect(run);
        currentStepIndex++;
        console.log("Challenge: run: currentStepIndex is " + currentStepIndex);
    }

    // --- Private Methods --------------------------------------------------------------

    function _runCurrentStep() {
        console.log("Challenge: _runCurrentStep: Called");
        requestNewStepConnections();
        currentStep.completed.connect(run);
        currentStep.run();
    }
}
