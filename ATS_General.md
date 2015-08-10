# ATS\_General() #
Is a comprehensive set of tests that run all the builtin tests, and determine if the software is working on a specific board.    ATS\_General() tests you can make The basic idea is to tie every pin starting at 0 to the next pin except the power, and ground. Also, leave the first set of RX, and TX pins free for serial communications so that test results can be returned. Pin 0 jumpered to pin 1. Pin 2 jumpered to Pin3. You can also use a prototyping board, or make a shield to have these settings. One bonus of the mega design is that it's compatible with the Uno.

## Configuration for the standard Arduino: ##
![https://sites.google.com/site/ricklonhelloworld/_/rsrc/1287718726153/arduino-test-suite/test-shield/TestShield328_bb.png](https://sites.google.com/site/ricklonhelloworld/_/rsrc/1287718726153/arduino-test-suite/test-shield/TestShield328_bb.png)

## Configuration for the Mega: ##
![https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShieldMega_bb.png](https://sites.google.com/site/arduinotestsuitelibrary/arduino-test-suite/test-shield/TestShieldMega_bb.png)

```

//************************************************************************
//* Arduino Test Suite
//* (C) 2010 by Mark Sproul
//* Open source as per standard Arduino code
//*
//************************************************************************
//* Aug 31, 2010 <MLS> Started on TestArduino
//* Oct 18, 2010 <MLS> Added memory testing
//************************************************************************


#include "WProgram.h"
#include "HardwareSerial.h"
#include "pins_arduino.h"
#include <ArduinoTestSuite.h>
#include "avr_cpunames.h"

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
#define kBoard_PinCount 20
#define kBoard_AnalogCount 6
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define kBoard_PinCount 70
#define kBoard_AnalogCount 16
#endif


//************************************************************************
void setup()
{ 
    short ii;
    uint8_t timerNumber;
    int startMemoryUsage;


    startMemoryUsage = ATS_GetFreeMemory();


    ATS_begin("Arduino", "general");


    //* test digital pins
    //* we start at 2 because 0/1 are RXD/TXD
    for (ii=2; ii<kBoard_PinCount; ii++)
    {
        ATS_Test_DigitalPin(ii);
    }

    //* test PWM pins
    //* we start at 2 because 0/1 are RXD/TXD
    for (ii=2; ii<kBoard_PinCount; ii++)
    {
        timerNumber = digitalPinToTimer(ii);
        if (timerNumber != NOT_ON_TIMER)
        {
            ATS_Test_PWM_Pin(ii);
        }
    }

    for (ii=0; ii<kBoard_AnalogCount; ii++)
    {
        ATS_Test_AnalogInput(ii);
    }

    #if (SERIAL_PORT_COUNT > 1)
    ATS_TestSerialLoopback(&Serial1, "Serial1");
    #endif
    #if (SERIAL_PORT_COUNT > 2)
    ATS_TestSerialLoopback(&Serial2, "Serial2");
    #endif
    #if (SERIAL_PORT_COUNT > 3)
    ATS_TestSerialLoopback(&Serial3, "Serial3");
    #endif

    ATS_Test_EEPROM();

    ATS_ReportMemoryUsage(startMemoryUsage);

    ATS_end();

}

//************************************************************************
void loop()
{

}
```