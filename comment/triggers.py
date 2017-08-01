# triggers.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from comment.event_manager import EventManager
from comment.locale import Locale
from comment.utils import text_to_speech, debug

from comment.events import QUIT_APP


class Triggers(object):
    """
    TODO: Description
    """

    TRIGGERS = {
        'SAY': 'say',
        'EXIT': 'exit'
    }

    def __init__(self):
        """
        TODO: Description
        """
        super(Triggers, self).__init__()

    def load(self):
        """
        TODO: Description
        """
        for trigger in self.TRIGGERS:
            self.TRIGGERS[trigger] = Locale.get_instance().get(self.TRIGGERS[trigger])

    def execute(self, command):
        """
        TODO: Description
        """
        try:
            trigger, arguments = command.split(' ', 1)
        except:
            trigger = command
            arguments = None

        debug('Triggers: execute: trigger is {} and arguments is {}'.format(trigger, arguments))

        if trigger not in self.TRIGGERS.itervalues():
            debug(
                '[ERROR] Triggers: execute: command {} does not have a recognised trigger'
                .format(command)
            )
            return False

        if trigger == self.TRIGGERS['SAY']:
            text_to_speech(arguments)

        elif trigger == self.TRIGGERS['EXIT']:
            EventManager.get_instance().trigger_event(QUIT_APP)

        return True

    def get_trigger(self, trigger_key):
        """
        TODO: Description
        """
        return self.TRIGGERS[trigger_key]
