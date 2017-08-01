#!/bin/bash

# push-to-pi.sh
#
# Sync


DEST_USER='radu'
# DEST_USER='kano'
DEST_IP='10.0.30.45'
# DEST_IP='10.0.30.230'
# DEST_IP='192.168.1.74'

DEST_DIR="$(basename `pwd`)"
DEST_STR="$(printf "%s@%s:~/%s" "$DEST_USER" "$DEST_IP" "$DEST_DIR")"

echo "rsync -ravz -e ssh $(pwd)/ $USERNAME $DEST_STR"
rsync -ravz -e ssh  \
    --exclude='.git' --exclude='*.pyc' --exclude='*.swp' --exclude='.DS_Store' \
    --exclude='*.o' --exclude='moc_*' --exclude='Makefile*' --exclude='.qmake*' \
    --exclude='debug' --exclude='release' \
    "$(pwd)/" "$USERNAME" "$DEST_STR"
