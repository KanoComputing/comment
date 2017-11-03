/**
 * InteractiveIDE.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3

import Controllers 1.0
import Widgets 1.0 as Widgets
import Widgets.Terminal 1.0


Rectangle {
    id: root

    property Challenge currentChallenge: cxx_challengeManager.currentChallenge

    color: "transparent"

    Terminal {
        id: terminal
        height: Math.round(parent.height * 0.9)

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 40
    }

    Widgets.IdeFooter {
        id: footer

        anchors.top: terminal.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
    }


    onCurrentChallengeChanged: {
        console.log("InteractiveIDE: onCurrentChallengeChanged: Called");
        currentChallenge.requestNewStepConnections.connect(connectCurrentStep);
        currentChallenge.requestOldStepDisconnect.connect(disconnectOldStep);
        currentChallenge.requestPrintText.connect(terminal.print_msg);
        currentChallenge.start();
    }

    function connectCurrentStep() {
        console.log("InteractiveIDE: connectCurrentStep: Called");
        var currentStep = cxx_challengeManager.currentChallenge.currentStep;

        currentStep.requestPrintText.connect(terminal.print_msg);
        currentStep.requestTypewriterText.connect(terminal.echo_msg);
        currentStep.requestPrompt.connect(terminal.prompt);
        terminal.response.connect(currentStep.userInput);
        // terminal.finished_writing.connect()
    }

    function disconnectOldStep() {
        console.log("InteractiveIDE: requestOldStepDisconnect: Called");
        var currentStep = cxx_challengeManager.currentChallenge.currentStep;

        currentStep.requestPrintText.disconnect(terminal.print_msg);
        currentStep.requestTypewriterText.disconnect(terminal.echo_msg);
        currentStep.requestPrompt.disconnect(terminal.prompt);
        terminal.response.disconnect(currentStep.userInput);
        // terminal.finished_writing.connect()
    }
}
