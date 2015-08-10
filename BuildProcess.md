# ATTENTION #
_This documentation is out of date please refer to:_

https://github.com/arduino/Arduino/wiki/Build-Process

# Overview #

A number of things have to happen for your Arduino code to get onto the Arduino board.  (Note: this description applies to versions 1.0.x of the Arduino software.) First, the Arduino environment performs some small pre-processing to turn your sketch into a C++ program.  It then gets passed to a compiler (avr-gcc), which turns the human readable code into machine readable instructions (or object files).  Then, your code gets combined with (linked against), the standard Arduino libraries that provide basic functions like digitalWrite() or Serial.print().  The result is a single Intel hex file, which contains the specific bytes that need to be written to the program memory of the chip on the Arduino board.  This file is then uploaded to the board: transmitted over the USB or serial connection via the bootloader already on the chip or with external programming hardware.

# Pre-Processing #

The Arduino environment performs a few transformations to your main sketch file (the concatenation of all the tabs in the sketch without extensions) before passing it to the avr-gcc compiler.

When your sketch is compiled, all tabs with no extension are concatenated together to form the "main sketch file" (C++).  Then, #include "Arduino.h" is added to your sketch.  This header file (found in the core folder for the currently selected board) includes all the definitions needed for the standard Arduino core. Next, the environment searches for function definitions within your main sketch file and creates declarations (prototypes) for them.

The #include statement and function prototypes are inserted after any comments or pre-processor statements (#includes or #defines), but before any other statements (including type declarations).  This means that if you want to use a custom type as a function argument, you should declare it within a separate header file.  Also, this generation isn't perfect: it won't create prototypes for functions that have default argument values, or which are declared within a namespace or class. To work around this, you can provide your own prototypes for such functions; prototypes will not be generated for functions that already have them.

No pre-processing is done to .c, .cpp, or .h files in a sketch.  Additionally, .h files in the sketch are not automatically #included from the main sketch file.  Further, if you want to call functions defined in a .c file from a .cpp file (like one generated from your sketch), you'll need to wrap its declarations in an 'extern "C" {}' block that is defined only inside of C++ files.

# Compilation #

Sketches are compiled by avr-gcc and avr-g++ according to the variables in the boards.txt file of the selected board's [platform](Platforms.md).

The include path includes the sketch's directory, the board's variant folder (a sub-directory of hardware/arduino/variants specified in boards.txt), the core folder (e.g. the hardware/arduino/core/arduino/ sub-folder of the Arduino application) and the avr include directory (hardware/tools/avr/avr/include/), as well as any library directories (in hardware/libraries/ and the libraries/ sub-directory of your sketchbook) which contain a header file which is included by the main sketch file.

Note that libraries referenced only by another library (and not the main sketch file) are not placed in the include path or linked against the sketch.  All libraries used (even indirectly by another library) must be #included by the main sketch file.  Also, libraries can't have arbitrary sub-folders.  Instead, a special sub-folder "utility", is searched for .c and .cpp files to link in; the "utility" folder is also added to the included path when compiling the library containing it - but not when compiling other files (e.g. headers in the "utility" folder won't be found if #included from the sketch).

When you verify or upload a sketch, it is built in a temporary directory in the system-wide temporary directory (e.g. /tmp on Linux).

The .c and .cpp files of the target are compiled and output with .o extensions to this directory, as is the main sketch file and any other .c or .cpp files in the sketch and any .c or .cpp files in any libraries which are #included in the sketch.

Before compiling each .c or .cpp file, an attempt is made to reuse the previously compiled .o file, which speeds up the build process. A special .d (dependency) file provides a list of all other files included by the source. The compile step is skipped if the .o and .d files exist and have timestamps newer than the source and all the dependent files. If the source or any dependent file has been modified, or any error occurs verifying the files, the compiler is run normally, writing a new .o & .d file.  After a new board is selected from the Tools menu, all .c and .cpp files are rebuilt on the next compile.

These .o files are then linked together into a static library and the main sketch file is linked against this library.  Only the parts of the library needed for your sketch are included in the final .hex file, reducing the size of most sketches.

The .hex file is the final output of the compilation which is then uploaded to the board.

If verbose output during compilation is checked in the Preferences dialog, the complete command line of each external command executed as part of the build process will be printed in the editor console.

# Uploading #

Sketches are uploaded by avrdude.  The upload process is also controlled by variables in the boards and main preferences files.  See the [platforms](Platforms.md) page for details.

If verbose output during upload is checked in the Preferences dialog, debugging information will be output to the editor console, including avrdude command lines and verbose output.