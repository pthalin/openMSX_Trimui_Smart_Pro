# openMSX for Trimui Smart Pro

<img height="50%" src="images/trimui_smart_pro.jpg"> 

### How to get your console
Please use these affiliate links when buying your Trimui to support me!  
[Trimui Smart Pro](https://s.click.aliexpress.com/e/_DC7NNMZ)

Accessories for Trimui Smart Pro  
[Protective Bag](https://s.click.aliexpress.com/e/_DnKA17f)  
[Screen Protector](https://s.click.aliexpress.com/e/_DCqp3jf)  
[Silicon Case](https://s.click.aliexpress.com/e/_Dk2vuOp)  
[Thumb Grip](https://s.click.aliexpress.com/e/_Dm0gxmz)

### How to install
IMPORTANT: You must have [Crossmix OS](https://github.com/cizia64/CrossMix-OS) installed to use openMSX. Save yourself some headache by using a branded SDCARD of good quality and not the noname card that you may get when buying the device.

Extract the openMSX [release archive](https://github.com/pthalin/openMSX_Trimui_Smart_Pro/releases/latest) in the "Emus" folder on the SDCARD (overwrite existing files). Run the "EmuCleaner" App after installation.

### How to use
Select a game in the MSX or MSX2 category and press the X button. This brings up a menu where you can select diffrent configurations.

Button mapping in openMSX

MENU - Open the Main Menu.  
START - Show/Hide the On-screen Keyboard.  
SELECT - Toggle 50/60 Hz (MSX2+/Turbo R only).  
A - Primary fire.  
B - Secondary fire.  
Y - Enable auto-fire (Turbo R only).  
X - Diable auto-fire (Turbo R only).  
L1 - Quick load state.  
R1 - Quick save state.  
L2 - Toggle Show FPS.  
R2 - Toggle Show Battery Level.
  
<p float="left">
<img width="300" src="images/osd_keyboard.png">
<img width="300" src="images/load_state.png"> 
</p>

#### Important
+ C-Bios only works for .rom files and it does not have Basic. Use MSX-Bios for .dsk files and games that need Basic.
+ Running MSX-Bios requires system roms to be installed. These will be automatically downloaded the first time you run it if you are connected to wifi.
+ Save States can be removed by deleting the .oms file in the folder "Emus/MSX2/.openMSX/savestates" folder.
+ For the game [Pampas & Selene](https://www.unepicfran.com/en/msx_pampas.html) use "openMsx (C-Bios MSX2+)" with the file "pampas_e.rom" to automatically apply the needed configuration. The rom file may also be renamed to "Pampas & Selene.rom".

#### Physical keyboard
A Bluetooth or USB keyboard can be used with openMSX. To use a USB keyboard you ned a [USB-C OTG Adapter](https://s.click.aliexpress.com/e/_DljXh1r) or a [USB-C Hub](https://s.click.aliexpress.com/e/_DlLiGnR). The keyboard must be connected before starting openMSX. Any of the two USB port on the Trimui Smart Pro can be used. A Bluetooth keyboard must be paired in the Trimui Settings before starting openMSX.

<img width="300" src="images/keyboard.jpg">

### How to build
You need Linux to build.  
Install the [patched SDK](https://github.com/pthalin/SDK_Trimui_Smart_Pro)  
Run "source build.sh" in the top dir.

### FAQ
Q: Why is it based on an old verion of openMSX?  
A: The compiler (GCC) for the Trimui is an old version and newer versions of openMSX requires a more recent version of the compiler.

### Thanks! 
Donation using [Ko-Fi](https://ko-fi.com/patriksretrotech) or [PayPal](https://www.paypal.com/donate/?business=UCTJFD6L7UYFL&no_recurring=0&item_name=Please+support+me%21&currency_code=SEK) are highly appreciated!

This is a based on [openMSX](https://github.com/openMSX/openMSX). A big thank you to the developers of openMSX for making an awsome emulator and providing help so I could complete this. 
