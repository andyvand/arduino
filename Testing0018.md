Help is welcome; try as many of these tests as you like.  Report your findings in the comments, including:
  * the operating system you tested on
  * on Linux, the versions of avr-gcc and avr-libc (for the core) or java (for the IDE) installed
  * the Arduino board you tested on
  * the test(s) attempted
  * the results

If found, please also add bugs to the [issues list](http://code.google.com/p/arduino/issues/list).  Also see the list of [issues addressed in Arduino 0018](http://code.google.com/p/arduino/issues/list?can=1&q=milestone=0018).

Core tests:

  1. Serial.end() - _ends serial communication and frees digital pins 0 and 1 for normal input and output._
    * test a: after a call to Serial.end(), can pins 0 and 1 be used for normal input and output?
    * test b: after a call to Serial.end(), will Serial.begin() re-enable serial communication?
    * test c: does Serial.end() work on all four Serial ports on the Arduino Mega?
  1. tone() and noTone() - _frequency generation_
    * test a: does tone() generate a square wave w/ 50% duty cycle on any pin?
    * test b: does tone() generate the correct frequency (across multiple frequencies / timer prescale factors)?
    * test c: does the tone() end after the specified duration?
    * test d: can tone() change the frequency of the wave being generated on a pin?
    * test e: can tone() work on different pins in sequence?
    * test f: does noTone() end a tone (with either specified or unlimited duration)?
  1. Serial.print(float, digits) - _variable precision printing of floating point numbers_
    * test a: does the number printed have the correct number of decimal digits?
    * test b: can the full range of floating point values be printed?
  1. Firmata
    * test a: are digital input values sent successfully?
    * test b: are analog input values sent successfully?
    * test c: can digital outputs be controlled?
    * test d: can analog outputs (PWM waves) be controlled?
    * test e: can servo motors be controlled?
  1. LiquidCrystal
    * test a: is there an absence of strange behavior when omitting the RW pin?
  1. Analog inputs
    * test a: do analog inputs 8 to 15 work properly on the Arduino Mega?
  1. micros() - _fixed incorrect check for timer 0 overflow_
    * test a: does the return value of micros() ever decrease from one call to the next (except on overflow)?
    * test b: does the return value micros() even jump significantly?

IDE tests:

  1. Third-party hardware - _support for boards.txt, bootloaders, cores, and programmers.txt in hardware sub-directory of the sketchbook directory_
    * test a: do boards listed in such a boards.txt file appear in the boards menu in the IDE?
    * test b: can a sketch be compiled for a third-party board that uses a core in its own platform (sub-directory of hardware)?
    * test c: can a sketch be compiled for a third-party board that uses the built-in arduino core?
    * test d: can a sketch be compiled for a third-party board that uses a core from another third-party platform (using the platform:core syntax in boards.txt)?
    * test e: can the bootloader from the same platform be burned onto a third-party board?
    * test f: can a built-in bootloader be burned onto a third-party board?
    * test g: can a bootloader from another third-party platform be burned onto a third-party board?
  1. Verbose output
    * test a: does holding down the shift key while pressing the **Compile / Verify** toolbar button generate verbose output?
    * test b: does holding down the shift key while pressing the **Upload** toolbar button generate verbose output?
  1. Saving
    * test a: are changes successfully saved when closing the last, modified, sketch (and clicking "Save")?
    * test b: are changes successfully saved when opening a sketch or creating a new sketch within an editor with unsaved changes (and clicking "Save")?
  1. File-names
    * test a: can a .cpp, .c, and .h file with the same name be added to a sketch and successfully compiled?
    * test b: does the IDE prevent the presence of a .cpp file with the same name as the sketch (whether upon creation of the .cpp file or renaming of the sketch)?
  1. Upload from disk image (.dmg)
    * test a: can the examples be successfully uploaded when Arduino.app is run from with the disk image (.dmg) on Mac OS X?