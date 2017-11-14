/**
 * Step.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import QtQuick 2.3
import Colours 1.0 as Colours


Item {
    id: root

    property string copy: "copy property not set!"
    property string hint: ""
    property string validate: ""
    property bool clear: false

    signal completed()

    signal requestPrintText(string text)
    signal requestTypewriterText(string text)
    signal requestPrompt()
    signal requestClear()


    onCompleted: {
        cxx_inputRunner.executeFinished.disconnect(_onExecuteFinished);
    }

    // --- Public Slot Methods ----------------------------------------------------------

    function run() {
        if (clear) {
            console.log("Step: run: Step needs clear beforehand, requesting terminal clear");
            requestClear();
        }

        requestPrintText(copy);

        if (validate != "") {
            console.log("Step: run: Step requires validation, requesting user prompt");
            requestPrompt();
        } else {
            console.log("Step: run: Step doesn't require validation, step complete");
            // TODO: Insert a sleep here before signaling to progress forward.
            completed();
        }
    }

    function userInput(text) {
        if (cxx_inputRunner.checkInstruction(text)) {
            console.log("Step: userInput: User entered instruction, retry");
            // TODO: Add a small ~0.5s delay here.
            requestPrompt();
            return;
        }

        if (!cxx_inputRunner.isValid(text, validate)) {
            if (hint != "") {
                console.log("Step: userInput: User input is not valid, requesting hint print");
                requestPrintText(hint);
            }
            console.log("Step: userInput: User input is not valid, requesting user prompt");
            // TODO: Add a small ~0.5s delay here.
            requestPrompt();
            return;
        }

        cxx_inputRunner.executeFinished.connect(_onExecuteFinished);
        cxx_inputRunner.execute(text);
    }

    // --- Private Slot Methods ---------------------------------------------------------

    function _onExecuteFinished(successful) {
        if (successful) {
            console.log("Step: _onExecuteFinished: Successful, step complete");
            completed();
        } else {
            console.log("Step: _onExecuteFinished: Script encountered error, requesting user prompt");
            var error = cxx_inputRunner.getError();
            if (error != "") {
                console.log("Step: _onExecuteFinished: Error retrieved, requesting error print");
                requestPrintText(
                    "<font color='%1'>".arg(Colours.Palette.tallPoppy) + error + "</font>"
                );
            }
            requestPrompt();
        }
    }
}
