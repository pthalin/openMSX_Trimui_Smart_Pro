#!/bin/sh

OM_DIR=/mnt/SDCARD/Emus/MSX2/openmsx
EMU_DIR=/mnt/SDCARD/Emus/MSX2

ROM_FILE=$(realpath "$1")

cd $OM_DIR

export OPENMSX_SYSTEM_DATA=$PWD/share
export HOME=$EMU_DIR

rom_name=$(echo $1 | tr '[:upper:]' '[:lower:]')
case "$rom_name" in
 *"pampas"* )
   echo "pampas"
   exec bin/openmsx -machine C-BIOS_MSX2+ -ext MegaFlashROM_SCC+_SD "$ROM_FILE" -romtype KonamiUltimateCollection
   ;;
 * )
   echo "Other"
   exec bin/openmsx -machine C-BIOS_MSX2+ "$ROM_FILE"
   ;;
esac
