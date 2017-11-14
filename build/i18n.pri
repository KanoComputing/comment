# i18n.pri
#
# Copyright (C) 2017 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
#
# TODO: description


load(kano_i18n)

lupdate_only {
    SOURCES += \
        $$files($$KANO.project_dir/*.qml, true)
}

TRANSLATIONS = \
    $$KANO.i18n_path/comment_en_US.ts \
    $$KANO.i18n_path/comment_es_AR.ts
