# Download #

The second release candidate of Arduino 1.0 is available (as of October 25, 2011):

  * Windows: http://files.arduino.cc/downloads/arduino-1.0-rc2.zip
  * Mac OS X: http://files.arduino.cc/downloads/arduino-1.0-rc2.dmg
  * Linux (32-bit): http://files.arduino.cc/downloads/arduino-1.0-rc2.tgz
  * Linux (64-bit): http://files.arduino.cc/downloads/arduino-1.0-rc2-64.tgz
  * Source: http://files.arduino.cc/downloads/arduino-1.0-rc2-src.tar.gz

The source code is hosted in the new-extension branch on GitHub: https://github.com/arduino/Arduino/tree/new-extension

If you find bugs, please open a [new issue](http://code.google.com/p/arduino/issues/list).  For general problems or discussion, use the [developers mailing list](http://mail.arduino.cc/mailman/listinfo/developers_arduino.cc).

# Environment (IDE) #

  * New file extension (.ino).
  * New toolbar icons: checkmark (verify) and arrow (upload).  (Nicholas Zambetti)
  * New color scheme, document icon, about image (ToDo).
  * Board name and serial port are shown in status line at the bottom of the editor. (from Wiring)
  * URLs in the sketch code are now clickable hyperlinks ([issue 148](https://code.google.com/p/arduino/issues/detail?id=148)) (Christian Maglie)
  * Progress bar shown during compilation and upload. (from Wiring)
  * Support for uploading sketches from within the IDE: hold shift while clicking upload or select "Upload Using Programmer" from the File menu.  Select programmer from the Tools menu of the IDE.
  * Verbose output (during compilation or uploading) now enabled from within the preferences dialog.

# Language (API) #

  * Switching to non-blocking Serial writes with a transmit buffer.
  * Serial.flush() now waits for transmission of outgoing data rather than discarding received incoming data.
  * Reimplementation of the SoftwareSerial library to support multiple ports (NewSoftSerial by Mikal Hart).
  * Removed Matrix and Sprite libraries.
  * Serial.print(byte) now prints the digits of the number as characters; use write() to send as a single byte.
  * write(), print(), and println() now return size\_t (unsigned int) instead of void ([issue 551](https://code.google.com/p/arduino/issues/detail?id=551)): number of bytes written.
  * write(str) in Print is no longer virtual, so subclasses of Print or Stream can't (but also don't need to) override it.
  * Added getWriteError(), clearWriteError(), and protected setWriteError() methods to Print; use to check for, clear, and set a write error flag.
  * Removed the ability to say "client == NULL" or "client != NULL" from Ethernet library; use "if (client)" or "if (!client)" instead.
  * Reimplementation of String class (Paul Stoffregen + additional modifications).
  * Added support for Flash-based strings using the F("string") syntax.
  * Added DHCP and DNS support to the Ethernet library (integration by Adrian McEwen).
  * Renamed Ethernet Client, Server, and UDP classes to EthernetClient, EthernetServer, and EthernetUDP to allow for simultaneous use of other networking libraries.
  * Modified UDP API:
    * beginPacket() / endPacket() for bracketing UDP packet construction
    * Inheriting from Stream, using write(), print(), and println() for UDP packet construction
    * parsePacket() for parsing incoming packets (and checking if there is one)
    * available(), read(), peek() for reading bytes of incoming packet
    * remoteIP(), remotePort() for information about incoming packet
  * Addition of IPAddress class (Adrian McEwen).
  * Modified Wire library to inherit from Stream; i.e. to use read(), write(), print(), println(), etc.  Bracket calls to those functions with beginTransmission() and endTransmission().
  * Adding support for multiple open files and directory iteration in SD card library (Limor Fried).
  * Added serialEvent() function, called automatically on reception of serial data if it exists.  Also, serialEvent1(), serialEvent2(), and serialEvent3() on the Mega.
  * Added find(), findUntil(), parseInt(), parseFloat(), readBytes(), readBytesUntil(), and setTimeout() to Stream ([issue 458](https://code.google.com/p/arduino/issues/detail?id=458) - Michael Margolis).
  * Updated Firmata to version 2.3 ([r71](https://code.google.com/p/arduino/source/detail?r=71)): analog inputs now numbered from 14 (not 16) when used as digital pins.

# Internals #

  * Renamed WProgram.h to Arduino.h.
  * Pin definitions separated from the core and stored in new variants/ sub-directory.  Specified by the _BOARD_.build.variant preference in boards.txt.
  * Added macros / constants for getting information about the properties of the board ([issue 490](https://code.google.com/p/arduino/issues/detail?id=490) and [issue 495](https://code.google.com/p/arduino/issues/detail?id=495))

# Tools #
  * Updated avrdude to 5.11 (and switched to arduino programmer type from stk500).