#!/bin/sh

OM_DIR=/mnt/SDCARD/Emus/MSX2/openmsx
EMU_DIR=/mnt/SDCARD/Emus/MSX2

ROM_FILE=$(realpath "$1")

cd $OM_DIR

export OPENMSX_SYSTEM_DATA=$PWD/share
export HOME=$EMU_DIR

rom_name=$(echo $1 | tr '[:upper:]' '[:lower:]')
case "$rom_name" in
 *".dsk"* )
  /mnt/SDCARD/System/usr/trimui/scripts/infoscreen.sh -m "C-Bios does not supppor .dsk files. Please use Turbo-R." -k " "
  exit
  ;;
 *"pampas"* )
   echo "pampas"
   exec bin/openmsx -machine C-BIOS_MSX2+ -ext MegaFlashROM_SCC+_SD "$ROM_FILE" -romtype KonamiUltimateCollection
   ;;
 * )
   echo "Other"
   exec bin/openmsx -machine C-BIOS_MSX2+ "$ROM_FILE"
   ;;
esac
