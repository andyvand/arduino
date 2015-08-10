# Arduino Test Suite Library #

This initial library was contributed by a collaboration between Mark Sproul, and Rick Anderson. The idea was to get a simple test suite going so that anyone can make tests and test cases for the Arduino software. Just as it should be easy to get going with programming an Arduino, we want it to be the same  for testing the Arduino.  Since this is the initial draft of documentation and code, we expect feedback, and are ready to address any issues, and add improvements. We monitor the Arduino developer mailing list regularly. Please send feed back there. And now onto the documentation:

## Arduino Test Suite Library ##

This library allows you to create standard test suite for the Arduino software. The goal is to provide a simple and standard way to build tests and tests cases any way you need to as long as you use a few simple principles, and the results return the standard [ArduinoTestResultFormat](ArduinoTestResultFormat.md). That can then be parsed by a continuous integration and test system. Which this library provides built in support for. Your tests can then be associated with various issues, and features. These tests can be added to the official list of tests that are run automatically every time code is changed in the official repository. An additional benefit is that these are standard Arduino sketches that you can on your own Arduinos.  You can test your work as you develop, or better yet create your tests first and as you could you should see the tests pass.

### Functions ###

  * [ATS\_begin()](ATS_begin.md)
  * [ATS\_end()](ATS_end.md)
  * [ATS\_PrintTestStatus()](ATS_PrintTestStatus.md)


### A Brief Introduction to the Arduino Test Suite Library ###

To take advantage of the Arduino Test Library include the ArduinoTestSuite.h file at the top of your code. Because the test results are returned via the serial interface so for all tests you also need to include WProgram.h, and HardwareSerial.h. Once include you are free to include other libraries as need to perform your test or tests. In the setup you can now configure your test or tests. To start the test you'll need to use:
```
ATS_begin("Arduino","My bare bones tests.");
```

Set the manufacture of the board or shield you are testing the software of, and test suite name. This initializes the serial interface, and anything that occurs after that line will be your test code. Once complete you now need to tell the test suite that you've done a test and what happened. Issue:
```
ATS_PrintTestsStatus("Bare bones test" , status);
```
This will indicate the test resulted in true or false. Numbering is not built in so if you want to number your tests put it in the test name like:
```
ATS_PrintTestsStatus("1. bare bones test" , status);
```
Now you need to tell the test it is complete. , so it can calculate the results and report back over serial what happened.
```
ATS_end();
```
### Example Tests: ###
```
Test of success
#include "WProgram.h"
#include "HardwareSerial.h"
#include <ArduinoTestSuite.h>

//************************************************************************
void setup()
{
     boolean result;
     ATS_begin("Arduino", "My bare bones tests");
     result = true;
     ATS_PrintTestStatus("My bare bones test", result);
     ATS_end();
}

void loop()
{
}
```

### Test result: ###
```
info.MANUFACTURER    = Arduino
info.CPU-NAME        = ATmega328P
info.GCC-Version     = 4.3.2
info.AVR-LibC-Ver    = 1.6.4
info.Compiled-date   = Oct 20 2010
info.Test-Suite-Name = My bare bones tests
info.Free-memory     = 1464 bytes
My bare bones test                                          ... ok
--------------------------
Ran 1 tests in 1.371s

OK
```

### Test with one success, and one failure. ###
```
#include "WProgram.h"
#include "HardwareSerial.h"
#include <ArduinoTestSuite.h>

//************************************************************************
void setup()
{
     boolean result;
     ATS_begin("Arduino", "My bare bones tests");
     result = true;
     ATS_PrintTestStatus("My bare bones test", result);
     result = false;
     ATS_PrintTestStatus("1. My bare bones test", result);
     ATS_end();
}

void loop()
{
}
```
### Test Result: ###
```
info.MANUFACTURER = Arduino
info.CPU-NAME = ATmega328P
info.GCC-Version = 4.3.2
info.AVR-LibC-Ver = 1.6.4
info.Compiled-date = Oct 20 2010
info.Test-Suite-Name = My bare bones tests
info.Free-memory = 1442 bytes
My bare bones test                             ... ok
1. My bare bones test                          ... FAIL
--------------------------
Ran 2 tests in 1.443s


FAILED (failures=1)
```

## Anatomy of a test result ##

Test results consist of a series of "info" fields, list of test name, and results. Followed by how many run in what time. With the ultimate summary at the end. OK if all good. FAILED with number of failures.

### Example: Testing for a memory leak ###

> You must keep the following in mind. Any new values created inside the memory test will use memory. So you must declare all the variables that consume memory at the top of setup prior to:
```
startMemoryUsage = ATS_GetFreeMemory();
```

Once this is done your starting memory is set. Anything that takes without putting back will be counted as a failure. The memory test is over when you call:
```
ATS_ReportMemoryUsage(startMemoryUsage);
```

Hint for debugging: put this test at the bottom of the code, and then you can move it higher into the code and see where the memory was lost. As soon as you get an "ok" the memory loss occurred below. Binary search will help you find the problem.
```
#include "WProgram.h"
#include "HardwareSerial.h"
#include <ArduinoTestSuite.h>


//************************************************************************
void setup()
{
    int startMemoryUsage;

    //startMemoryUsage must be set directly before ATS_begin
    startMemoryUsage = ATS_GetFreeMemory();
    ATS_begin("Arduino", "Skeleton Test");
    /*
     * Test Run Start
     * Test one passes because result is set to true
     * Test two fails becuase result is set to false
     * You can test memory for any set of tests by using the ATS_ReportMemoryUsage test
     * There is also a way to print current memeory for debugging
     */
    ATS_PrintTestStatus("1. Test of true test status", true);
    ATS_PrintTestStatus("2. Test of false test status, this will fail.", false);
    ATS_ReportMemoryUsage(startMemoryUsage);
    /*
     * Test Run End
     */
    ATS_end();
}
//************************************************************************
void loop()
{
}
```
### Test Result: ###
```
info.MANUFACTURER = Arduino
info.CPU-NAME = ATmega328P
info.GCC-Version = 4.3.2
info.AVR-LibC-Ver = 1.6.4
info.Compiled-date = Oct 20 2010
info.Test-Suite-Name = Skeleton Test
info.Free-memory = 1322 bytes
1. Test of true test status                         ... ok
2. Test of false test status, this will fail.       ... FAIL
Memory Usage ... ok
--------------------------
Ran 3 tests in 1.508s


FAILED (failures=1)
```
### Examples ###

  * [ATS\_Skeleton](ATS_Skeleton.md): Test skeleton you can build your own tests from
  * [ATS\_General](ATS_General.md): Tests Digital Read/Write, Analog Read/Write, PWM, EEPROM, and Serial loopback.
  * [ATS\_Constants](ATS_Constants.md): Tests the constants as spec'ed by Arduino documentation
  * [ATS\_StringTest](ATS_StringTest.md): Test features of the String Library
  * [ATS\_StringIndexOfMemory](ATS_StringIndexOfMemory.md): Tests whether memory was lost during the use of strings


## Builtin Tests ##
These can be useful in combination with a custom test.

  * [ATS\_ReportMemoryUsage(int \_memoryUsageAtStart)](ATS_ReportMemoryUsage.md)
  * [ATS\_Test\_DigitalPin(uint8\_t digitalPinToTest)](ATS_Test_DigitalPin.md)
  * [ATS\_Test\_PWM\_Pin(uint8\_t digitalPinToTest)](ATS_Test_PWM_Pin.md)
  * [ATS\_Test\_AnalogInput(uint8\_t analogPintoTest)](ATS_Test_AnalogInput.md)
  * [ATS\_Test\_EEPROM(void)](ATS_Test_EEPROM.md)
  * [ATS\_TestSerialLoopback(HardwareSerial \*theSerialPort, char \*serialPortName)](ATS_TestSerialLoopback.md)


## See Also ##

  * ArduinoTestProcess
  * ArduinoTestPlan
  * ArduinoTestResultFormat
  * ArduinoListofTests