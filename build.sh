# build with "source build.sh" in folder
 
cd openmsx-16.0/
make staticbindist OPENMSX_TARGET_CPU=aarch64 OPENMSX_TARGET_OS=trimui OPENMSX_FLAVOUR=opt
cd ..

rm openmsx_trimui_smart_pro_crossmix.zip
rm -rf build
mkdir build
mkdir build/MSX
mkdir build/MSX2
mkdir build/MSX2/openmsx
cp -r ./openmsx-16.0/derived/aarch64-trimui-opt-3rd/bindist/install/bin/ ./build/MSX2/openmsx/
cp -r ./openmsx-16.0/derived/aarch64-trimui-opt-3rd/bindist/install/share/ ./build/MSX2/openmsx/
cp crossmix/MSX/* build/MSX
cp crossmix/MSX2/* build/MSX2
cp crossmix/settings/settings.xml build/MSX2/openmsx/share/
cp -r crossmix/resources/ build/MSX2/openmsx

# Replace symlink with file
rm build/MSX2/openmsx/share/machines/msx1.xml 
rm build/MSX2/openmsx/share/machines/msx1_eu.xml 
rm build/MSX2/openmsx/share/machines/msx2.xml 
rm build/MSX2/openmsx/share/machines/msx2_eu.xml 
rm build/MSX2/openmsx/share/machines/msx2plus.xml
rm build/MSX2/openmsx/share/machines/turbor.xml

cp build/MSX2/openmsx/share/machines/National_CF-3300.xml build/MSX2/openmsx/share/machines/msx1.xml
cp build/MSX2/openmsx/share/machines/Toshiba_HX-10.xml build/MSX2/openmsx/share/machines/msx1_eu.xml
cp build/MSX2/openmsx/share/machines/Sony_HB-F900.xml build/MSX2/openmsx/share/machines/msx2.xml
cp build/MSX2/openmsx/share/machines/Philips_NMS_8250.xml build/MSX2/openmsx/share/machines/msx2_eu.xml
cp build/MSX2/openmsx/share/machines/Panasonic_FS-A1WSX.xml build/MSX2/openmsx/share/machines/msx2plus.xml 
cp build/MSX2/openmsx/share/machines/Panasonic_FS-A1GT.xml build/MSX2/openmsx/share/machines/turbor.xml

cd build/
zip -r ../openmsx_trimui_smart_pro_crossmix.zip ./*
cd ..
