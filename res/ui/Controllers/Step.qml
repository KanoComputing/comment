/**
 * Step.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


Component {
    id: root

    readonly property string copy
    readonly property string hint
    readonly property string validate


    function initialise() {

    }

    function reset() {
        copy = 'copy property not set!';
        hint = ''
        validate = ''
    }
}
