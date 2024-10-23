#!/bin/sh
# Startup script for openMSX.
# Run this to start openMSX; running the executable directly does not work.

#TODO: Check if we have sysroms. If not downlaod from file-hunter.com

rom_path=$(realpath "$1")

rom_name=$(echo $1 | tr '[:upper:]' '[:lower:]')

echo $rom_path

cd /mnt/SDCARD/Emus/MSX2/openmsx

export OPENMSX_SYSTEM_DATA=$PWD/share

case "$rom_name" in
 *"pampas"* )
   echo "pampas"
   exec bin/openmsx -machine C-BIOS_MSX2+ -ext MegaFlashROM_SCC+_SD "$rom_path" -romtype KonamiUltimateCollection
   ;;
 * )
   echo "Other"
   exec bin/openmsx -machine C-BIOS_MSX2+ "$rom_path"
   ;;
esac

cd ..