/**
 * terminal.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPLv2
 *
 * Emulates a terminal with custom messages and prompts.
 */


import QtQuick 2.3
import QtQuick.Layouts 1.2

import Widgets.Terminal 1.0


Item {
    id: terminal
    implicitHeight: scroll.implicitHeight

    property int prompt_count: 0

    // Triggered when the typewriter animation (from echo_msg()) finishes.
    signal finished_writing()

    // Triggered when the user hits ENTER in the prompt (from prompt()).
    signal response(string msg);


    Flickable {
        id: scroll

        contentHeight: messages.height
        contentWidth: messages.width
        contentY: Math.max(contentHeight - height, 0)

        interactive: false
        anchors.fill: parent

        Column {
            id: messages
            spacing: TerminalSettings.font_size
            width: scroll.width
            height: Math.max(scroll.height, childrenRect.height)
        }
    }

    /**
     * Print a message to the terminal with a typewriter animation.
     */
    function echo_msg(msg) {
        var component = Qt.createComponent('terminal_text.qml'),
            obj = component.createObject(messages, {
                'anchors.left': messages.left,
                'anchors.right': messages.right
            });

        obj.typewriter(msg.replace(/\n/g, '<br>'));
        obj.finished_writing.connect(terminal.finished_writing);
    }

    /**
     * Print a message to the terminal
     */
    function print_msg(msg) {
        var component = Qt.createComponent('terminal_text.qml'),
            obj = component.createObject(messages, {
                'anchors.left': messages.left,
                'anchors.right': messages.right
            });

        obj.text = msg.replace(/\n/g, '<br>');
        terminal.finished_writing();
    }

    /**
     * Display a prompt and ask for a message.
     */
    function prompt(args) {
        var args = args || {},
            prefix = args.prefix || '',
            prompt_marker = args.prompt_marker || TerminalSettings.prompt_marker,
            completion = args.completion || [],
            component = Qt.createComponent('terminal_prompt.qml'),
            obj = component.createObject(messages, {
                prefix: prefix,
                prompt_marker: prompt_marker,
                completion: completion,
                'anchors.left': messages.left,
                'anchors.right': messages.right
            });
        obj.response.connect(terminal.response);
        prompt_count++;
    }

    /**
     * Remove all objects from the terminal.
     */
    function clear() {
        for (var index = messages.children.length - 1; index >= 0; index--) {
            if (messages.children[index].destroy) {
                messages.children[index].destroy();
            }
        }
    }
}
