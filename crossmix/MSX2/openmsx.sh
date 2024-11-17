#!/bin/sh

OM_DIR=/mnt/SDCARD/Emus/MSX2/openmsx
EMU_DIR=/mnt/SDCARD/Emus/MSX2

ROM_FILE=$(realpath "$1")

cd $OM_DIR

export OPENMSX_SYSTEM_DATA=$PWD/share
export HOME=$EMU_DIR

rom_name=$(echo $1 | tr '[:upper:]' '[:lower:]')

case "$rom_name" in
 *.zip)
  file_in_zip="$(/mnt/SDCARD/System/bin/7zz l -ba "$ROM_FILE")"
  case "$file_in_zip" in
    *".dsk"* )
      /mnt/SDCARD/System/usr/trimui/scripts/infoscreen.sh -m "C-Bios does not supppor .dsk files. Please use MSX-Bios." -k " "
      exit
      ;;
    * )
    exec bin/openmsx -machine C-BIOS_MSX2+ "$ROM_FILE"
    ;;
  esac
  ;;
 *".dsk"* )
  /mnt/SDCARD/System/usr/trimui/scripts/infoscreen.sh -m "C-Bios does not supppor .dsk files. Please use MSX-Bios." -k " "
  exit
  ;;
 *"pampas"* )
   exec bin/openmsx -machine C-BIOS_MSX2+ -ext MegaFlashROM_SCC+_SD "$ROM_FILE" -romtype KonamiUltimateCollection
   ;;
 * )
   exec bin/openmsx -machine C-BIOS_MSX2+ "$ROM_FILE"
   ;;
esac
