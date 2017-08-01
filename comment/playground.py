# playground.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from comment.challenge_step import ChallengeStep
from comment.triggers import Triggers
from comment.terminal import Terminal
from comment.locale import Locale
from comment.utils import read_json

from comment.paths import PLAYGROUND_FILE_PATH


class Playground(object):
    """
    TODO: Description
    """

    def __init__(self):
        """
        TODO: Description
        """
        super(Playground, self).__init__()

        self.steps_data = dict()
        self.step = ChallengeStep()
        self.triggers = Triggers()

    def load(self):
        """
        TODO: Description
        """
        playground_data = read_json(PLAYGROUND_FILE_PATH)
        self.steps_data = playground_data['steps']

        self.step.load()
        self.triggers.load()

    def run(self):
        """
        TODO: Description
        """
        for step_data in self.steps_data:
            self.step.initialise(step_data)
            self.step.run()

        while True:
            user_input = Terminal.get_instance().user_input()
            if not self.triggers.execute(user_input):
                cmd = user_input.split(' ', 1)[0]
                Terminal.get_instance().typewriter_echo(
                    Locale.get_instance().get('invalid_command').format(cmd)
                )
