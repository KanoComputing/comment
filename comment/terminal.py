# terminal.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import sys
import time
import termios
import atexit

original_state = None
SPEED_FACTOR = 1

TOP_PADDING = 0
LEFT_PADDING = 0


class Terminal(object):
    """
    TODO: Description
    """

    PROMPT = "user@kano ~ $ "

    _singleton_instance = None

    @staticmethod
    def get_instance():
        if not Terminal._singleton_instance:
            Terminal()

        return Terminal._singleton_instance

    def __init__(self):
        """
        TODO: Description
        """
        if Terminal._singleton_instance:
            raise Exception("This class is a singleton!")
        else:
            Terminal._singleton_instance = self

    def typewriter_echo(self, string, sleep=0, trailing_linebreaks=1):
        """
        TODO: Description
        """
        self._set_echo(False)

        self._write_flush(LEFT_PADDING * ' ')

        for character in string:
            if character == ' ':
                # Sleep for a little longer between words
                time.sleep(0.075 * SPEED_FACTOR)
            elif character in ['.', ',', '?', '!']:
                # The sleep is a little longer for punctuation
                time.sleep(0.05 * SPEED_FACTOR)
            else:
                time.sleep(0.025 * SPEED_FACTOR)

            self._write_flush(character)

        time.sleep(sleep + 0.3 * SPEED_FACTOR)
        self._write_flush(trailing_linebreaks * '\n')

        self._set_echo(True)
        self._discard_input()

    def user_input(self):
        """
        TODO: Description
        """
        self._discard_input()
        try:
            return raw_input(self.PROMPT)
        except EOFError:
            return ''

    def clear_screen(self, top_padding=True):
        """
        TODO: Description
        """
        sys.stderr.write("\x1b[2J\x1b[H")
        if top_padding:
            print TOP_PADDING * '\n'
        sys.stderr.flush()

    # --- Private Helpers ---------------------------------------------------------------

    def _write_flush(self, string):
        """
        TODO: Description
        """
        sys.stdout.write(string)  # TODO: set encoding to UTF-8
        sys.stdout.flush()

    def _set_echo(self, enabled=True):
        """
        TODO: Description
        """
        if not sys.stdin.isatty():
            return

        fd = sys.stdin.fileno()
        attrs = termios.tcgetattr(fd)

        if enabled:
            attrs[3] = attrs[3] | termios.ECHO
        else:
            attrs[3] = attrs[3] & ~termios.ECHO

        termios.tcsetattr(fd, termios.TCSADRAIN, attrs)

    def _discard_input(self):
        """
        TODO: Description
        """
        termios.tcflush(sys.stdin.fileno(), termios.TCIOFLUSH)

    # --- Are these needed ? ------------------------------------------------------------

    def set_control(self, enabled=True):
        """
        TODO: Description
        """
        if not sys.stdin.isatty():
            return

        fd = sys.stdin.fileno()
        attrs = termios.tcgetattr(fd)

        if enabled:
            attrs[0] = attrs[0] | termios.IXON
            attrs[0] = attrs[0] | termios.IXOFF

            attrs[6][termios.VSUSP] = '\x1a'
            attrs[6][termios.VQUIT] = '\x1c'
            attrs[6][termios.VKILL] = '\x15'
            attrs[6][termios.VINTR] = '\x03'
            attrs[6][termios.VEOF] = '\x04'
        else:
            attrs[0] = attrs[0] & ~termios.IXON
            attrs[0] = attrs[0] & ~termios.IXOFF

            attrs[6][termios.VSUSP] = '\x00'
            attrs[6][termios.VQUIT] = '\x00'
            attrs[6][termios.VKILL] = '\x00'
            attrs[6][termios.VINTR] = '\x00'
            attrs[6][termios.VEOF] = '\x00'

        termios.tcsetattr(fd, termios.TCSADRAIN, attrs)

    def restore_original_state(self):
        """
        TODO: Description
        """
        if sys.stdin.isatty() and original_state:
            fd = sys.stdin.fileno()
            termios.tcsetattr(fd, termios.TCSADRAIN, original_state)
            reset_overscan()

    def save_original_state(self):
        """
        TODO: Description
        """
        global original_state

        if sys.stdin.isatty() and not original_state:
            fd = sys.stdin.fileno()
            original_state = termios.tcgetattr(fd)
            atexit.register(restore_original_state)
