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

    property int currentStepIndex: 0
    property Step currentStep: steps[currentStepIndex]
    property bool isCompleted: false
    property int totalSteps: steps.length

    signal challengeCompleted(string challengeId, int challengeIndex)

    signal requestPrintText(string text)
    signal requestNewStepConnections()
    signal requestOldStepDisconnect()


    function start() {
        console.log("Challenge: start: Starting first step");
        requestPrintText(name);
        _runCurrentStep();
    }

    function run() {
        console.log("Challenge: run: Called");

        if (currentStepIndex + 1 >= steps.length) {
            console.log("Challenge: run: Challenge completed");
            challengeCompleted(objectName, index);
            cxx_challengeManager.nextChallenge();
            return;
        }
        requestOldStepDisconnect();
        currentStep.stepCompleted.disconnect(run);
        currentStepIndex++;
        console.log("Challenge: run: currentStepIndex is " + currentStepIndex);
    }

    onCurrentStepChanged: {
        console.log("Challenge: onCurrentStepChanged: Called");
        _runCurrentStep();
    }

    function _runCurrentStep() {
        console.log("Challenge: _runCurrentStep: Called");
        requestNewStepConnections();
        currentStep.stepCompleted.connect(run);
        currentStep.run();
    }

    function reset() {
        name = "name property not set!";
        index = 0;
        steps = [];
        currentStep = 0;
        totalSteps = 0;
    }
}
