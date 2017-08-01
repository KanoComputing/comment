# locale.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import imp

from comment.paths import LANGUAGE_FILE_PATH
from comment.utils import debug


class Locale(object):
    """
    TODO: Description
    """

    _singleton_instance = None

    @staticmethod
    def get_instance():
        if not Locale._singleton_instance:
            Locale()

        return Locale._singleton_instance

    def __init__(self):
        """
        TODO: Description
        """
        if Locale._singleton_instance:
            raise Exception("This class is a singleton!")
        else:
            Locale._singleton_instance = self

        self.language = dict()

    def load(self):
        """
        TODO: Description
        """
        self.language = imp.load_source('language', LANGUAGE_FILE_PATH).language

        debug('Locale: load: language is {}'.format(self.language))

    def get(self, key, arguments=list()):
        """
        TODO: Description
        """
        if arguments:
            argument_strings = [self.get(argument) for argument in arguments]
            return self.language[key].format(*argument_strings)
        else:
            return self.language[key]
