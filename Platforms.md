As of version 0018, the Arduino environment supports multiple platforms: collections of boards, bootloaders, cores, and programmers.  The built-in **arduino** platform is located within the distribution; others may be installed in the **hardware** sub-folder of the sketchbook folder.  This document describes the structure and organization of the files and folders in such a platform.

# Boards #

The Arduino environment supports multiple target boards with different chips (currently, only AVRs), CPU speeds, or bootloaders.  These are defined in boards.txt.  A board is specified by multiple variables prefixed with the same keyword (shown here as _BOARD_).  The file consists of multiple lines with the format _key=value_.  Lines that start with a `#` are comments and ignored.

Boards have many variables, including:

  * _BOARD_.name: the name to display in the **Boards** menu

Variables controlling the process of building sketches for the board:

  * _BOARD_.build.mcu: the microcontroller on the board (e.g. "atmega328" or "atmega1280").

  * _BOARD_.build.f\_cpu: the clock speed at which the microcontroller operates (normally "16000000L", or, for an ATmega168 running on its internal clock, "8000000L").

  * _BOARD_.build.core: the location of the core to link sketches against when compiling for the board. This may be the name of a folder in the **core** sub-folder of the platform (e.g. "arduino") or a value of the format _platform_:_core_, where _platform_ is the name of the folder of another platform (e.g. the built-in "arduino") and _core_ is a folder in that platform's **core** folder.

Variables controlling the upload process:

  * _BOARD_.upload.protocol: the protocol that avrdude should use to talk to the board (typically "stk500").

  * _BOARD_.upload.speed: the speed (baud rate) avrdude should use when uploading sketches (e.g. "19200").

  * _BOARD_.upload.disable\_flushing: set to true to disable manual flushing of the serial port from Java before avrdude is called to do the upload.

  * _BOARD_.upload.maximum\_size: the maximum size for a sketch on the board (dependent on the chip and the size of the bootloader).

  * ~~_BOARD_.upload.using: the name of a programmer to use instead of the bootloader when uploading sketches to the board (optional).  The value should be the prefix of a key in the programmers.txt file (e.g. "usbtinyisp") or a value in the format _platform_:_programmer_ where _platform_ is the name of the folder of another platform (e.g. the built-in "arduino" platform) and _programmer_ is the key for a programmer in that platform's programmers.txt.  If this variable is specified (and not equal to "bootloader"), the _BOARD_.upload.protocol and _BOARD_.upload.speed variables are ignored.~~ (no longer supported in Arduino 1.0)

Variables controlling the process of burning a bootloader onto the board:

  * _BOARD_.bootloader.low\_fuses: the byte to write to the low fuses of the microcontroller when burning the bootloader (e.g. "0xFF")

  * _BOARD_.bootloader.high\_fuses: the byte to write to the high fuses of the microcontroller (e.g. "0xDA")

  * _BOARD_.bootloader.extended\_fuses: the byte to write to the extended fuses (e.g. 0x05).  Note that avrdude (used by Arduino) uses 0 for unused fuse bits, whereas AVR Studio uses 1; this byte's value may need to be changed when moving between the two.

  * _BOARD_.bootloader.path: the location of the folder containing the bootloader .hex file.  This may be the name of a sub-folder of the **bootloader** sub-folder of the board's platform, or a value of the form _platform_:_path_, where _platform_ is the name of the folder of another platform, and _path_ is a sub-folder of its **bootloaders** sub-folder.  _Note:_ the bootloader file and path are optional; if omitted, the "burn bootloader" command will simply set the fuses.

  * _BOARD_.bootloader.file: the name of the .hex file (without any folder names or paths).  _Note:_ the bootloader file and path are optional; if omitted, the "burn bootloader" command will simply set the fuses.

  * _BOARD_.bootloader.unlock\_bits: the byte to write to the lock fuses of the microcontroller to unlock it before burning the bootloader.

  * _BOARD_.bootloader.lock\_bits: the byte to write to the lock fuses of the microcontroller to lock it after burning the bootloader.

# Bootloaders #

The **bootloaders** sub-folder of a platform contains the bootloaders for the boards in the platform.  These should appear as .hex files in a sub-folder of the **bootloaders** folder.  Often, the source code for the bootloader is also included, along with a Makefile for building the .hex file.

# Cores #

A core is a set of .c, .cpp, and .h files that implement the basic Arduino functions for a platform.  Each core appears as a sub-folder of the **cores** sub-folder of a platform.

A core should include at least the following files:

  * Arduino.h: an #include statement for this header file is automatically inserted into each sketch as part of the BuildProcess.  It should contain declarations for the functions, constants, and types in the core.  (Prior to Arduino 1.0, WProgram.h was used instead.)

  * main.cpp: a conventional location in which to specify the **main()** function of the sketch.  It should call **setup()** once and **loop()** over and over again.

# Programmers #

Programmers may be specified in the **programmers.txt** file in a platform.  This file has a format similar to the **boards.txt** file, but with the following variables:

  * _PROGRAMMER_.name: the name to display in the **Burn Bootloader** menu

  * _PROGRAMMER_.communication: either "serial" for programmers that use a serial device (to be selected from the **Tools > Serial Port** menu), "usb" for those that use the "-P usb" parameter to avrdude, or omitted for other programmer types.

  * _PROGRAMMER_.protocol: the programmer's protocol, passed as the "-c" parameter to avrdude.

  * _PROGRAMMER_.force: whether or not to send the "-F" parameter to avrdude, which ignores signature mismatches.  Defaults to false if omitted.

  * _PROGRAMMER_.speed: a baud rate to send as the "-b" parameter to avrdude (optional).