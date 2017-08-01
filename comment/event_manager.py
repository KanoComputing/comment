# event_manager.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


class EventManager(object):
    """
    TODO: Description
    """

    _singleton_instance = None

    @staticmethod
    def get_instance():
        if not EventManager._singleton_instance:
            EventManager()

        return EventManager._singleton_instance

    def __init__(self):
        """
        TODO: Description
        """
        if EventManager._singleton_instance:
            raise Exception("This class is a singleton!")
        else:
            EventManager._singleton_instance = self

        self.events = dict()

    def start_listening(self, event_name, listener):
        """
        TODO: Description
        """
        if event_name not in self.events:
            self.events[event_name] = list()

        self.events[event_name].append(listener)

    def stop_listening(self, event_name, listener):
        """
        TODO: Description
        """
        self.events[event_name].remove(listener)

        if len(self.events[event_name]) == 0:
            del self.events[event_name]

    def trigger_event(self, event_name, *args):
        """
        TODO: Description
        """
        if event_name not in self.events:
            return

        for listener in self.events[event_name]:
            listener(*args)
