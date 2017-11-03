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
    name: qsTr("Count")
    index: 2

    steps: [
        Step {
            copy: qsTr(
                "I can also count using the range() function, type say(\"range(1,10)\")"
            )
            hint: qsTr(
                "Type say(\"range(1,10)\") and press [enter]"
            )
            validate: "say(\"range(1,10)\")"
        },

        Step {
            copy: qsTr(
                "I counted from 1 up to 10, try typing say(\"range(15,10)\"). What do" +
                " you think will happen?"
            )
            hint: qsTr(
                "Type say(\"range(15,10)\") and press [enter]"
            )
            validate: "say(\"range(15,10)\")"
        },

        Step {
            copy: qsTr(
                "The range() function can count up but will never count over the" +
                " second number."
            )
        }
    ]
}
