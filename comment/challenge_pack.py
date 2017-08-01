# challenge_pack.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from comment.challenge import Challenge
from comment.savefile import Savefile


class ChallengePack(object):
    """
    TODO: Description
    """

    def __init__(self):
        """
        TODO: Description
        """
        super(ChallengePack, self).__init__()

        self.pack_name = ''
        self.pack_data = dict()
        self.challenge = Challenge()

    def initialise(self, pack_name, pack_data):
        """
        TODO: Description
        """
        self.pack_name = pack_name
        self.pack_data = pack_data

    def load(self):
        """
        TODO: Description
        """
        current_challenge = Savefile.get_instance().get_data()['challenge']
        self.challenge.initialise(current_challenge, self.pack_data[current_challenge])
        self.challenge.load()

    def run(self):
        """
        TODO: Description
        """
        # current_challenge = Savefile.get_instance().get_data()['challenge']
        # self.challenge.set_data(self.name, self.data[current_challenge])

        self.challenge.run()

    def on_challenge_completed(self, challenge_name, next_challenge, next_pack):
        """
        TODO: Description
        """
        self.challenge.set_data(next_challenge, self.challenge_data[next_challenge])
        self.run()
