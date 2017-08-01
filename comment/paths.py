# paths.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from os import sep
from os.path import abspath, dirname, expanduser, join


PROJECT_CODENAME = abspath(dirname(__file__)).rsplit(sep, 1)[1]

SRC_INSTALL_DIR = '/usr/lib'
RES_INSTALL_DIR = '/usr/share'
BASE_SRC_DIR = join(SRC_INSTALL_DIR, PROJECT_CODENAME)
BASE_RES_DIR = join(RES_INSTALL_DIR, PROJECT_CODENAME)
LOCAL_DIR = abspath(join(dirname(__file__), '..'))
HOME_DIR = expanduser('~')

if not LOCAL_DIR.startswith(SRC_INSTALL_DIR):
    BASE_SRC_DIR = LOCAL_DIR
    BASE_RES_DIR = LOCAL_DIR

RESOURCES_DIR = join(BASE_RES_DIR, 'res')

print 'paths.py: BASE_SRC_DIR is', BASE_SRC_DIR
print 'paths.py: BASE_RES_DIR is', BASE_RES_DIR
print 'paths.py: RESOURCES_DIR is', RESOURCES_DIR

CHALLENGES_DIR = join(RESOURCES_DIR, 'challenges')
PLAYGROUND_FILE_NAME = 'playground.json'
PLAYGROUND_FILE_PATH = join(CHALLENGES_DIR, PLAYGROUND_FILE_NAME)

BASE_SAVE_DIR = join(RESOURCES_DIR, 'savefile')
BASE_SAVE_DATA_NAME = 'savefile_data.py'
BASE_SAVE_DATA_PATH = join(BASE_SAVE_DIR, BASE_SAVE_DATA_NAME)

LOCALES_DIR = join(RESOURCES_DIR, 'locales')
LANGUAGE_FILE_NAME = 'language.py'
LANGUAGE_FILE_PATH = join(LOCALES_DIR, LANGUAGE_FILE_NAME)

print 'paths.py: LANGUAGE_FILE_PATH is', LANGUAGE_FILE_PATH

SAVE_DIR = join(HOME_DIR, '.' + PROJECT_CODENAME)
SAVE_FILE_NAME = 'savefile.json'
SAVE_FILE_PATH = join(SAVE_DIR, SAVE_FILE_NAME)
