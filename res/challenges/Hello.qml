/**
 * Hello.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


import Controllers 1.0
import Colours 1.0


Challenge {
    name: qsTr("Hello")
    index: 1

    hasPlayground: false
    playgroundPlays: 3

    steps: [
        Step {
            copy: qsTr(
                "Did you know you can make your computer speak?\n" +
                "Try it, type <font color='%1'><b>say(\"hello\")</b></font>" +
                " and press [enter]"
            ).arg(Palette.atlantis)

            hint: qsTr(
                "Oops, make sure you type all the highlighted symbols."
            )
            validate: "say(\"hello\")"
        },

        Step {
            copy: qsTr(
                "Cool! Let's make me say something else, type" +
                " <font color='%1'><b>say(\"nice to meet you\")</b></font>" +
                " and press [enter]"
            ).arg(Palette.atlantis)

            hint: qsTr(
                "Type <font color='%1'><b>say(\"nice to meet you\")</b></font>" +
                " and press [enter]"
            )
            validate: "say(\"nice to meet you\")"
        },

        Step {
            copy: qsTr(
                "Make me say a funny word like \"moo\", and type" +
                " <font color='%1'><b>say(\"moo\")</b></font>\n" +
                "Try some more words!"
            ).arg(Palette.atlantis)

            validate: "say(\"moo\")"  // TODO: Support regex, this should be say("*")
        }
    ]
}
