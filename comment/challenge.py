# challenge.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from comment.challenge_step import ChallengeStep
from comment.event_manager import EventManager
from comment.savefile import Savefile
from comment.utils import debug

from comment.events import CHALLENGE_COMPLETED


class Challenge(object):
    """
    TODO: Description
    """

    def __init__(self):
        """
        TODO: Description
        """
        super(Challenge, self).__init__()

        self.challenge_name = ''
        self.next_challenge = ''
        self.steps_data = dict()
        self.step = ChallengeStep()
        self.current_step = 0

    def initialise(self, challenge_name, challenge_data):
        """
        TODO: Description
        """
        self.challenge_name = challenge_name
        self.next_challenge = challenge_data['next_challenge']
        self.steps_data = challenge_data['steps']
        self._reset()

    def load(self):
        """
        TODO: Description
        """
        self.current_step = Savefile.get_instance().get_data()['step']
        self.step.load()

    def run(self):
        """
        TODO: Description
        """
        if self.current_step == -1:
            debug('Challenge: run: Challenge is already completed')
            self._challenge_completed()
            return

        for step_index in range(self.current_step, len(self.steps_data)):
            debug('Challenge: run: step_index is {}'.format(step_index))
            step_data = self.steps_data[step_index]
            Savefile.get_instance().get_data()['step'] = step_index
            self.step.initialise(step_data)
            self.step.run()

        Savefile.get_instance().get_data()['step'] = -1
        self._challenge_completed()

    def _challenge_completed(self):
        """
        """
        EventManager.get_instance().trigger_event(
            CHALLENGE_COMPLETED,
            self.challenge_name, self.next_challenge
        )
        self._reset

    def _reset(self):
        """
        """
        self.current_step = 0
