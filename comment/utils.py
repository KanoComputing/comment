# utils.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import os
import json
import platform


DEBUG = False


def read_file_contents(path):
    """
    TODO: Description
    """
    if os.path.exists(path):
        with open(path) as infile:
            return infile.read().strip()


def read_json(filepath):
    """
    TODO: Description
    """
    return json.loads(read_file_contents(filepath))


def write_json(filepath, data, sort_keys=True):
    """
    TODO: Description
    """
    with open(filepath, 'w') as outfile:
        json.dump(data, outfile, indent=2, sort_keys=sort_keys)


def ensure_dir(directory):
    """
    TODO: Description
    """
    if not os.path.exists(directory):
        os.makedirs(directory)


def text_to_speech(text):
    """
    TODO: Description
    """
    cmd_template = ''

    if platform.system() == 'Darwin':
        cmd_template = "say '{}'"
    elif platform.system() == 'Linux':
        cmd_template = "espeak '{}' > /dev/null 2>&1"
    else:
        return

    escaped_characters_text = json.dumps(text)
    cmd = cmd_template.format(escaped_characters_text)
    rc = os.system(cmd)
    if rc:
        debug('[ERROR] utils.py: text_to_speech: cmd {} failed with rc {}'.format(cmd, rc))


def make_terminal_fullscreen():
    """
    TODO: Description
    """
    if platform.system() == 'Linux':
        os.system('wmctrl -r "Make Me Talk" -b toggle,maximized_vert')


def debug(msg):
    """
    TODO: Description
    """
    global DEBUG

    if DEBUG:
        try:
            from kano.logging import logger
            logger.debug(msg)
        except:
            print msg
