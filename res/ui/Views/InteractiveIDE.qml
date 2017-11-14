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
        anchors.margins: 7
    }


    onCurrentChallengeChanged: {
        console.log("InteractiveIDE: onCurrentChallengeChanged: Called");
        var challenge = currentChallenge;

        challenge.requestNewStepConnections.connect(_connectCurrentStep);
        challenge.requestOldStepDisconnect.connect(_disconnectOldStep);
        challenge.requestPlaygroundConnections.connect(_connectPlayground);
        challenge.requestPlaygroundDisconnect.connect(_disconnectPlayground);

        challenge.requestPrintText.connect(terminal.print_msg);
        challenge.requestClear.connect(terminal.clear);

        challenge.start();
    }

    // --- Private Methods --------------------------------------------------------------

    function _connectCurrentStep() {
        console.log("InteractiveIDE: _connectCurrentStep: Called");
        var step = cxx_challengeManager.currentChallenge.currentStep;

        step.requestPrintText.connect(terminal.print_msg);
        step.requestTypewriterText.connect(terminal.echo_msg);
        step.requestPrompt.connect(terminal.prompt);
        step.requestClear.connect(terminal.clear);
        terminal.response.connect(step.userInput);
        // terminal.finished_writing.connect()
    }

    function _disconnectOldStep() {
        console.log("InteractiveIDE: _disconnectOldStep: Called");
        var step = cxx_challengeManager.currentChallenge.currentStep;

        step.requestPrintText.disconnect(terminal.print_msg);
        step.requestTypewriterText.disconnect(terminal.echo_msg);
        step.requestPrompt.disconnect(terminal.prompt);
        step.requestClear.disconnect(terminal.clear);
        terminal.response.disconnect(step.userInput);
        // terminal.finished_writing.connect()
    }

    function _connectPlayground() {
        console.log("InteractiveIDE: _connectPlayground: Called");
        var playground = cxx_challengeManager.currentChallenge.playground;

        playground.requestPrintText.connect(terminal.print_msg);
        playground.requestPrompt.connect(terminal.prompt);
        terminal.response.connect(playground.userInput);
    }

    function _disconnectPlayground() {
        console.log("InteractiveIDE: _disconnectPlayground: Called");
        var playground = cxx_challengeManager.currentChallenge.playground;

        playground.requestPrintText.disconnect(terminal.print_msg);
        playground.requestPrompt.disconnect(terminal.prompt);
        terminal.response.disconnect(playground.userInput);
    }
}
