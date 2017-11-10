# functions.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import os
import platform


def say(text):
    """
    TODO: Description
    """

    cmd = ''

    if platform.system() == 'Darwin':
        cmd = 'say "{}"'.format(text)
    elif platform.system() == 'Linux':
        cmd = 'espeak "{}"'.format(text)

    if not cmd:
        return

    os.system(cmd)
