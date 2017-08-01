# savefile.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


import os
import imp

from comment.utils import read_json, write_json, ensure_dir
from comment.utils import debug

from comment.paths import BASE_SAVE_DATA_PATH, SAVE_DIR, SAVE_FILE_PATH


class Savefile(object):
    """
    TODO: Description
    """

    _singleton_instance = None

    @staticmethod
    def get_instance():
        if not Savefile._singleton_instance:
            Savefile()

        return Savefile._singleton_instance

    def __init__(self):
        """
        TODO: Description
        """
        if Savefile._singleton_instance:
            raise Exception("This class is a singleton!")
        else:
            Savefile._singleton_instance = self

        self.data = dict()

    def load(self):
        """
        TODO: Description
        """
        if os.path.exists(SAVE_FILE_PATH):
            self.data = read_json(SAVE_FILE_PATH)
        else:
            self.data = imp.load_source('savefile_data', BASE_SAVE_DATA_PATH).base_savefile

        debug('Savefile: load: data is {}'.format(self.data))

    def save(self):
        """
        TODO: Description
        """
        ensure_dir(SAVE_DIR)
        write_json(SAVE_FILE_PATH, self.data)

    def get_data(self):
        """
        TODO: Description
        """
        return self.data
