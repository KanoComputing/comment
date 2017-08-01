# language.py
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: Description


language = {

    # --- Generic messages --------------------------------------------------------------

    'type_this': _("TYPE {}"),
    'type_this_then': _("TYPE {}\n{}"),
    'press_enter': _("Then press [ENTER]\n"),
    'invalid_command': _("{}: command not found"),

    # --- Commands ----------------------------------------------------------------------

    'say': _("say"),
    'exit': _("exit"),

    # --- Challenge: example1 -----------------------------------------------------------

    'welcome': _("Ready to make me talk?\n"),
    'say_hello': _("say") + " " + _("hello"),

    # --- Challenge: example2 -----------------------------------------------------------

    'knock_knock': _("Knock knock!\n"),
    'say_who_is_there': _("say") + " " + _("Who's there?"),
    'art': _("Art\n"),
    'say_art_who': _("say") + " " + _("Art who?"),
    'r2_d2': _("R2-D2\n"),
    'say_makes_no_sense': _("say") + " " + _("That doesn't make any sense in Spanish!"),

    # --- Playground --------------------------------------------------------------------

    'welcome_playground': _("Nice work! You made me talk.\n"
        "Try making me say more things by typing commands below.\n"),
    'can_type_exit': _("You can type 'exit' to quit the app at any time.\n")
}
