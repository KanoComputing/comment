# challenge_manager.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import os

from comment.challenge import Challenge
from comment.event_manager import EventManager
from comment.savefile import Savefile
from comment.utils import read_json, debug

from comment.events import CHALLENGE_COMPLETED, ALL_CHALLENGES_COMPLETED
from comment.paths import CHALLENGES_DIR


class ChallengeManager(object):
    """
    TODO: Description
    """

    def __init__(self):
        """
        TODO: Description
        """
        super(ChallengeManager, self).__init__()

        self.challenges_data = dict()
        self.challenge = Challenge()

    def load(self):
        """
        TODO: Description
        """
        for challenge_file in os.listdir(CHALLENGES_DIR):
            if not challenge_file.endswith('.json'):
                continue

            challenge_name, file_extension = challenge_file.rsplit('.', 1)

            challenge_path = os.path.join(CHALLENGES_DIR, challenge_file)
            debug('ChallengeManager: load: challenge_path is {}'.format(challenge_path))
            self.challenges_data[challenge_name] = read_json(challenge_path)

        current_challenge = Savefile.get_instance().get_data()['challenge']
        self.challenge.initialise(current_challenge, self.challenges_data[current_challenge])
        self.challenge.load()

        EventManager.get_instance().start_listening(
            CHALLENGE_COMPLETED, self.on_challenge_completed
        )

    def run(self):
        """
        TODO: Description
        """
        self.challenge.run()

    def on_challenge_completed(self, challenge_name, next_challenge):
        """
        TODO: Description
        """
        debug(
            'ChallengeManager: on_challenge_completed: Challenge {} finished,'
            ' next one is {}'.format(challenge_name, next_challenge)
        )

        if not next_challenge:
            EventManager.get_instance().trigger_event(ALL_CHALLENGES_COMPLETED)
            return

        Savefile.get_instance().get_data()['challenge'] = next_challenge
        Savefile.get_instance().get_data()['completed_challenges'].append(challenge_name)

        self.challenge.initialise(next_challenge, self.challenges_data[next_challenge])
        self.run()
