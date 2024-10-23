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

cd build/
zip -r ../openmsx_trimui_smart_pro_crossmix.zip ./*
cd ..