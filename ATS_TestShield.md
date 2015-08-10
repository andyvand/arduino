#ATS\_TestShield and Wiring

There needs to be a quick way to test the software on an Arduino board. Also, some test might require special hardware and might make sense to be done as protoboard, or a custom designed shield. You'll need to provide instructions with your test on how to create that board.

For example the   ATS\_General() tests you can make The basic idea is to tie every pin starting at 0 to the next pin except the power, and ground. Also, leave the first set of RX, and TX pins free for serial communications so that test results can be returned. Pin 0 jumpered to pin 1. Pin 2 jumpered to Pin3. You can also use a prototyping board, or make a shield to have these settings. One bonus of the mega design is that it's compatible with the Uno.

The builtin tests, and the ATS\_General() tests are designed assuming you have done this.

Configuration for the standard Arduino:
![https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShield328_bb.png](https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShield328_bb.png)


Configuration for the Mega:
![https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShieldMega_bb.png](https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShieldMega_bb.png)