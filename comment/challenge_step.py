# challenge_step.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from comment.triggers import Triggers
from comment.terminal import Terminal
from comment.locale import Locale
from comment.utils import debug


class ChallengeStep(object):
    """
    TODO: Description
    """

    MAX_USER_TRIES = 3

    def __init__(self):
        """
        TODO: Description
        """
        super(ChallengeStep, self).__init__()

        self.copy = ''
        self.arguments = list()
        self.validate = ''
        self.clear_screen = True
        self.triggers = Triggers()
        self.try_count = 1

    def initialise(self, step_data):
        """
        TODO: Description
        """
        self.copy = step_data['copy']
        self.arguments = step_data['arguments']
        self.validate = step_data['validate']
        self.clear_screen = step_data['clear_screen']
        self._reset()

    def load(self):
        """
        TODO: Description
        """
        self.triggers.load()

    def run(self):
        """
        TODO: Description
        """
        debug('ChallengeStep: copy is {}'.format(self.copy))
        debug('ChallengeStep: arguments is {}'.format(self.arguments))
        debug('ChallengeStep: validate is {}'.format(self.validate))
        debug('ChallengeStep: clear_screen is {}'.format(self.clear_screen))

        text = Locale.get_instance().get(self.copy, arguments=self.arguments)

        if not self.validate:
            Terminal.get_instance().typewriter_echo(text)
            return

        user_input = ''
        expected_input = Locale.get_instance().get(self.validate)
        debug('ChallengeStep: run: expected_input is {}'.format(expected_input))

        while (not self._is_user_input_valid(user_input, expected_input) and
               self.try_count <= self.MAX_USER_TRIES):

            Terminal.get_instance().typewriter_echo(text)

            user_input = Terminal.get_instance().user_input()
            debug('ChallengeStep: run: user_input is {}'.format(user_input))
            debug('ChallengeStep: run: try_count is {}'.format(self.try_count))

            self.try_count += 1

        if self.try_count > self.MAX_USER_TRIES:
            self.triggers.execute(expected_input)
        else:
            self.triggers.execute(user_input)

        if self.clear_screen:
            Terminal.get_instance().clear_screen()

    def _is_user_input_valid(self, user_input, expected_input):
        """
        TODO: Description
        """
        user_input = user_input.strip()
        expected_input = expected_input.strip()

        return (
            user_input == expected_input or
            user_input == Locale.get_instance().get('exit')
        )

    def _reset(self):
        """
        TODO: Description
        """
        self.try_count = 1
