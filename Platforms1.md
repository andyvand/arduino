# An overview of the platform architecture proposed for Arduino 1.5 #

## Base layout ##

The hardware folder is split into multiple levels of organization:

  * _package_ (or packager): a folder containing board definitions and code for one or more architectures (e.g. arduino)
  * _platform_: a microcontroller architecture (e.g. avr or sam)

The idea is that third-parties can supply a single-folder package which provide support for all their hardware, across multiple microcontroller architectures.

Within the user's Arduino sketchbook folder, `hardware/_PACKAGE_/_PLATFORM_/` contains:
  * a **`boards.txt`** file containing boards definitions
  * a **`cores`** folder containing one or more folders with the implementation of the Arduino API
  * a **`platform.txt`** file that contains build process definitions (e.g. compiler and command-line arguments)
  * a **`programmers.txt`** file with programmer definitions
  * a **`system`** folder containing system libraries (e.g. those supplied by the microcontroller manufacturer)
  * a **`tools`** folder containing the toolchain binaries
  * a **`variants`** folder, containing one or more folders with code specific to particular hardware variations
  * a **`bootloaders`** folder
  * a **`libraries`** folder

all these files targets the containing platform but its possible to reference other packages.

To update an existing 1.0 core you need to move all files contained in `hardware/_CORE_/` to a new `hardware/_CORE_/avr/` folder and update some definitions inside `boards.txt` file (a migration page will be available once the core format specification stabilizes).

### Example ###

If the Arduino hardware folder were installed as third-party hardware folder, it would be organized like this:
  * `hardware/`**`arduino/`** - the root for the Arduino hardware
  * `hardware/arduino/`**`avr/`** - contains the definitions for the AVR-based Arduino boards
  * `hardware/arduino/avr/`**`boards.txt`** - definitions of the AVR boards
  * `hardware/arduino/avr/`**`platform.txt`** - definitions of the AVR build process
  * `hardware/arduino/avr/`**`cores/arduino`**`/` - the core providing the Arduino API for AVR boards
  * `hardware/arduino/avr/`**`variant`**`/...` - a folder containing the various pin definitions for AVR boards
  * `hardware/arduino/`**`sam`**`/` - support for the ARM-based Arduino boards
  * `hardware/arduino/sam/`**`boards.txt`** - definitions of the ARM boards
  * `hardware/arduino/sam/`**`platform.txt`** - definitions of the ARM build process
  * `hardware/arduino/sam/`**`cores/arduino`**`/` - the core providing the Arduino API for ARM boards
  * `hardware/arduino/sam/`**`variant`**`/...` - a folder containing the various pin definitions for ARM boards
  * `hardware/arduino/sam/`**`system`**`/...` - this folder contains libraries provided from chip manufacturer, and linked through the build process defined in _platform.txt_

Let's suppose we want to add two new cores for AVR, we should put them in the following place:
  * `hardware/arduino/avr/cores/`**`C`**`/` - a hypothetical core providing support for straight AVR C on Arduino boards
  * `hardware/arduino/avr/cores/`**`rtos`**`/` - a hypothetical core providing support for an RTOS on Arduino boards

## How to use core/variant from another packager ##

The `boards.txt` file now allows the use of a core or variant from another packager (without the need to provide another copy of such core/variant).
The syntax is:
  * `BOARD.build.core = [`**`PACKAGE`**`:]`**`CORE`**
  * `BOARD.build.variant = [`**`PACKAGE`**`:]`**`VARIANT`**
for example if we made a board called "xyz" that is Leonardo compatible we can simply create an entry in a 3rd-party `boards.txt` file like this:
```
xyz.build.code = arduino:arduino
xyz.build.variant = arduino:leonardo
```
or use a 3rd party specific variant but keep the arduino core:
```
xyz.build.code = arduino:arduino
xyz.build.variant = xyz
```

the referred core/variant may be within another package, but not a different platform (i.e. you can't have an ARM boards.txt file that refers to an AVR core).  _PACKAGE_ is optional, if omitted, the _CORE_ or _VARIANT_ value is assumed to be within the same package as the boards.txt file.

## Build process ##

The build process has been broken out into a configuration file called **`platforms.txt`**. Now is possible to customize such process without the need to hack the IDE's java source code. Let's see the content of this file.

The first part of `platform.txt` containts some common use variables like compile flags, linker options etc. These variables are named using the prefix `compiler.` or `build.` and can be overriden from the `boards.txt`, for example, to enable a compiler flag when user selects a specific board from the IDE.

The second part are the _recipes_: these are the compiler command line used to build the actual project. The command line is composed using the `{variable_name}` syntax, for example:
```
## Compile c files
recipe.c.o.pattern="{compiler.path}{compiler.c.cmd}" {compiler.c.flags} -mmcu={build.mcu} -DF_CPU={build.f_cpu} -D{software}={runtime.ide.version} {build.extra_flags} {includes} "{source_file}" -o "{object_file}"
```
Note that the double quotes `" "` are used to make a single command line argument out of many variables or to ensure that a variable containing (optional) spaces like `{source_file}` is seen as a single command line argument.

The third part is the _tools_ section. Here we define the tools that are used to upload sketches or shown in the "Programmers" menu to burn bootloaders.
The main defined _actions_ for each tools are:
  * **`upload`**: this action is used when the user "upload a sketch"
  * **`program`**: this action is used when the user "upload a sketch using a programmer"
  * **`erase`** and **`bootloader`**: these actions are used when the user "burn a bootloader"

## What about libraries? ##

Assuming `PACKAGE` and `PLATFORM` are the package and platform for the selected board, the IDE will search for libraries inside the following folders (in order of priority):

  1. `arduino/hardware/`**`PACKAGE/PLATFORM/libraries`**
  1. `arduino/`**`libraries`**
  1. `SKETCHBOOKFOLDER/`**`libraries`**

Note that the libraries in folder 1. are available only when the specific platform and package are selected, while the other libraries are always available even if the currently selected CPU architecture is incompatible.

## Fat (multiplatform) libraries ##

How can I make a 3rd party library for multiple architecure?

First you must put an empty file called `library.properties` inside the library root folder. The Arduino IDE looks for this file and if found handles the library as a "fat" (multi-platform) library.

Second, you must create a folder for every architecure you are going to support.
For example a Servo fat-library will have the following layout:

  * **`Servo/`**
  * `Servo/`**`avr`**`/...` - AVR implementation
  * `Servo/`**`sam`**`/...` - ARM implementation
  * `Servo/`**`xxxx`**`/...` - xxxx architecture implementation
  * `Servo/`**`examples`**`/...` - Examples, valid for all architecture
  * `Servo/`**`library.properties`** - empty file

When the user chooses a board the IDE automatically selects the correct library implementation for the board's architecture. If there isn't such implementation the library will be ignored.

The examples are shown only if the library has an implementation for the currently selected board architecture.

The packagers should agree on a common name for every available architecture.

The `library.properties` file is currently empty, it's here to give a safe way to detect fat libraries against non-fat libraries. The content of this file is reserved for future extensions.

## Open questions ##

  * What about core files that are shared between platforms (e.g. String, Stream)?  Where do they go?