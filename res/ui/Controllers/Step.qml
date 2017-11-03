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

    signal stepCompleted()

    signal requestPrintText(string text)
    signal requestTypewriterText(string text)
    signal requestPrompt()


    function run() {
        requestPrintText(copy);

        if (validate != "") {
            console.log("Step: run: Step requires validation, requesting user prompt");
            requestPrompt();
        } else {
            console.log("Step: run: Step doesn't require validation, step complete");
            stepCompleted();
        }
    }

    function userInput(text) {
        if (_isValid(text)) {
            console.log("Step: userInput: User input is valid, step complete");
            stepCompleted();
        } else {
            if (hint != "") {
                console.log("Step: userInput: User input is NOT valid, requesting hint print");
                requestPrintText(hint);
            }
            console.log("Step: userInput: User input is NOT valid, requesting user prompt");
            requestPrompt();
        }
    }

    function _isValid(input) {
        return (input == validate);
    }

    function reset() {
        copy = "copy property not set!";
        hint = ""
        validate = ""
    }
}
