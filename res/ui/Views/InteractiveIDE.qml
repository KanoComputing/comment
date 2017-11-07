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
    color: "transparent"

    property Challenge currentChallenge: cxx_challengeManager.currentChallenge

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
        var challenge = currentChallenge;

        challenge.requestNewStepConnections.connect(connectCurrentStep);
        challenge.requestOldStepDisconnect.connect(disconnectOldStep);
        challenge.requestPrintText.connect(terminal.print_msg);
        challenge.requestClear.connect(terminal.clear);
        challenge.start();
    }

    function connectCurrentStep() {
        console.log("InteractiveIDE: connectCurrentStep: Called");
        var step = cxx_challengeManager.currentChallenge.currentStep;

        step.requestPrintText.connect(terminal.print_msg);
        step.requestTypewriterText.connect(terminal.echo_msg);
        step.requestPrompt.connect(terminal.prompt);
        step.requestClear.connect(terminal.clear);
        terminal.response.connect(step.userInput);
        // terminal.finished_writing.connect()
    }

    function disconnectOldStep() {
        console.log("InteractiveIDE: disconnectOldStep: Called");
        var step = cxx_challengeManager.currentChallenge.currentStep;

        step.requestPrintText.disconnect(terminal.print_msg);
        step.requestTypewriterText.disconnect(terminal.echo_msg);
        step.requestPrompt.disconnect(terminal.prompt);
        step.requestClear.disconnect(terminal.clear);
        terminal.response.disconnect(step.userInput);
        // terminal.finished_writing.connect()
    }
}
