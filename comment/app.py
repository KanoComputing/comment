# app.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import sys
import atexit

from comment.challenge_manager import ChallengeManager
from comment.playground import Playground
from comment.event_manager import EventManager
from comment.terminal import Terminal
from comment.locale import Locale
from comment.savefile import Savefile
from comment.utils import make_terminal_fullscreen

from comment.events import ALL_CHALLENGES_COMPLETED, QUIT_APP


class App(object):
    """
    TODO: Description
    """

    def __init__(self):
        """
        TODO: Description
        """
        super(App, self).__init__()

        self.challenge_manager = ChallengeManager()
        self.playground = Playground()

        make_terminal_fullscreen()
        atexit.register(self.on_quit_app)

    def load(self):
        """
        TODO: Description
        """
        Locale.get_instance().load()
        Savefile.get_instance().load()

        self.challenge_manager.load()
        self.playground.load()

        EventManager.get_instance().start_listening(
            ALL_CHALLENGES_COMPLETED, self.on_all_challenges_completed
        )
        EventManager.get_instance().start_listening(
            QUIT_APP, self.on_quit_app
        )

    def run(self):
        """
        TODO: Description
        """
        Terminal.get_instance().clear_screen()
        self.challenge_manager.run()

    def save(self):
        """
        TODO: Description
        """
        Savefile.get_instance().save()

    def on_all_challenges_completed(self):
        """
        TODO: Description
        """
        # Terminal.get_instance().clear_screen()
        self.playground.run()

    def on_quit_app(self):
        """
        TODO: Description
        """
        self.save()
        sys.exit(0)
