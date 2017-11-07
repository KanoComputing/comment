/**
 * Hello.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import Controllers 1.0


Challenge {
    name: qsTr("Hello")
    index: 1

    steps: [
        Step {
            copy: qsTr(
                "Did you know you can make your computer speak?\n" +
                "Try it, type say(\"hello\") and press [enter]"
            )
            hint: qsTr(
                "Oops, make sure you type all the highlighted symbols."
            )
            validate: "say(\"hello\")"
        },

        Step {
            copy: qsTr(
                "Cool! Let's make me say something else, type say(\"nice to meet you\")" +
                " and press [enter]"
            )
            hint: qsTr(
                "Type say(\"nice to meet you\") and press [enter]"
            )
            validate: "say(\"nice to meet you\")"
        },

        Step {
            copy: qsTr(
                "Make me say a funny word like \"moo\", and type say(\"moo\")\n" +
                "Try some more words!"
            )
            validate: "say(\"moo\")"  // TODO: Support regex, this should be say("*")
        }
    ]
}
