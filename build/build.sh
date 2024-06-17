#!/bin/sh

gcc -o create_dirs_files main.c `pkg-config --cflags --libs poppler-glib`
