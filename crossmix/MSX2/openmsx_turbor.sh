#!/bin/sh
# Startup script for openMSX.
# Run this to start openMSX; running the executable directly does not work.

rom_path=$(realpath "$1")

rom_name=$(echo $1 | tr '[:upper:]' '[:lower:]')


cd /mnt/SDCARD/Emus/MSX2/openmsx

export OPENMSX_SYSTEM_DATA=$PWD/share

server="https://download.file-hunter.com/System%20ROMs/machines/panasonic"

sys_roms="fs-a1st_firmware.rom 
fs-a1st_kanjifont.rom"

for f in $sys_roms
do
  if [ -f "./share/systemroms/$f" ]; then
    echo "Found sysrom $f"
  else
    echo "Downloading sysrom $f " 
    curl --fail-early --connect-timeout 10 -k -A "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/81.0" "$server/$f" -o ./share/systemroms/$f
  fi
done

exec bin/openmsx -machine Panasonic_FS-A1ST "$rom_path" -ext scc+

cd ..
