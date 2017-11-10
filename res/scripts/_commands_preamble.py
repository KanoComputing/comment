# _commands_preamble.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


from os.path import abspath, join, dirname;
import sys;
# "import json;
sys.path.append(abspath(join(dirname('.'), 'libs')));
# "print json.dumps(sys.path, indent=4);
from pycomment.functions import say;
