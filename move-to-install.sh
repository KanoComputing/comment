#!/bin/bash

# move-to-install.sh
#
# Install project from local


BINARIES_INSTALL_PATH=/usr/bin
PYTHON_INSTALL_PATH=/usr/lib/python2.7/dist-packages
RESOURCES_INSTALL_PATH=/usr/share/comment
DOT_APP_INSTALL_PATH=/usr/share/applications
APP_ICON_INSTALL_PATH=/usr/share/icons/Kano/66x66/apps

# Turn on debugging.
set -x


# Copying all the files.
sudo cp bin/* $BINARIES_INSTALL_PATH
sudo cp -r comment $PYTHON_INSTALL_PATH
sudo cp -r res $RESOURCES_INSTALL_PATH
sudo cp res/icon/comment-app.png $APP_ICON_INSTALL_PATH
sudo cp res/icon/comment.app $DOT_APP_INSTALL_PATH

# Turn off debugging.
set +x
