#!/bin/sh
# Startup script for openMSX.
# Run this to start openMSX; running the executable directly does not work.

rom_path=$(realpath "$1")

cd /mnt/SDCARD/Emus/MSX2/openmsx

export OPENMSX_SYSTEM_DATA=$PWD/share

exec bin/openmsx -machine C-BIOS_MSX1 "$rom_path"


