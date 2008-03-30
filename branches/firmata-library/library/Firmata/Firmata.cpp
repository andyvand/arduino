/*
  Firmata.cpp - Firmata library
  Copyright (c) 2007-2008 Free Software Foundation.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//******************************************************************************
//* Includes
//******************************************************************************

extern "C" {
    // AVR LibC Includes
#include <inttypes.h>
#include <stdlib.h>

    // use the abs in WConstants.h, not the one in stdlib.h
#undef abs
  
    // Wiring Core Includes
#include "WConstants.h"
}


#include "Firmata.h"
#include "EEPROM.h"
#include "HardwareSerial.h"


//******************************************************************************
//* Definitions
//******************************************************************************

//******************************************************************************
//* Constructors
//******************************************************************************

FirmataClass::FirmataClass(void)
{
    systemReset();
}

//******************************************************************************
//* Public Methods
//******************************************************************************

/* begin method for overriding default serial bitrate */
void FirmataClass::begin(void)
{
    blinkVersion();
    Serial.begin(115200);
    delay(300);
    printVersion();
}

/* begin method for overriding default serial bitrate */
void FirmataClass::begin(long speed)
{
    blinkVersion();
    Serial.begin(speed);
    delay(300);
    printVersion();
}

// output the protocol version message to the serial port
void FirmataClass::printVersion(void) {
    Serial.print(REPORT_VERSION, BYTE);
    Serial.print(FIRMATA_MINOR_VERSION, BYTE);
    Serial.print(FIRMATA_MAJOR_VERSION, BYTE);
}

void FirmataClass::blinkVersion(void)
{
    // flash the pin with the protocol version
    pinMode(VERSION_BLINK_PIN,OUTPUT);
    pin13strobe(2,1,4); // separator, a quick burst
    delay(500);
    pin13strobe(FIRMATA_MAJOR_VERSION, 200, 400);
    delay(500);
    pin13strobe(2,1,4); // separator, a quick burst
    delay(500);
    pin13strobe(FIRMATA_MINOR_VERSION, 200, 400);
    delay(500);
    pin13strobe(2,1,4); // separator, a quick burst
}

//------------------------------------------------------------------------------
// Serial Receive Handling

int FirmataClass::available(void)
{
    return Serial.available();
}

void FirmataClass::processInput(void)
{
    int inputData = Serial.read(); // this is 'int' to handle -1 when no data
    int command;
    
    // most commands have byte(s) of data following the command
    if( (waitForData > 0) && (inputData < 128) ) {  
        waitForData--;
        storedInputData[waitForData] = inputData;
        if( (waitForData==0) && executeMultiByteCommand ) { // got the whole message
            switch(executeMultiByteCommand) {
            case ANALOG_MESSAGE:
                if(currentAnalogCallback) {
                    (*currentAnalogCallback)(multiByteChannel,
                                             (storedInputData[0] << 7)
                                             + storedInputData[1]);
                }
                break;
            case DIGITAL_MESSAGE:
                if(currentDigitalCallback) {
                    (*currentDigitalCallback)(multiByteChannel,
                                              (storedInputData[0] << 7)
                                              + storedInputData[1]);
                }
                break;
            case SET_PIN_MODE:
                if(currentPinModeCallback)
                    (*currentPinModeCallback)(storedInputData[1], storedInputData[0]);
                break;
            case REPORT_ANALOG:
                if(currentReportAnalogCallback)
                    (*currentReportAnalogCallback)(multiByteChannel,storedInputData[0]);
                break;
            case REPORT_DIGITAL:
                if(currentReportDigitalCallback)
                    (*currentReportDigitalCallback)(multiByteChannel,storedInputData[0]);
                break;
            }
            executeMultiByteCommand = 0;
        }	
    } else {
        // remove channel info from command byte if less than 0xF0
        if(inputData < 0xF0) {
            command = inputData & 0xF0;
            multiByteChannel = inputData & 0x0F;
        } else {
            command = inputData;
            // commands in the 0xF* range don't use channel data
        }
        switch (command) { // TODO: these needs to be switched to command
        case ANALOG_MESSAGE:
        case DIGITAL_MESSAGE:
        case SET_PIN_MODE:
            waitForData = 2; // two data bytes needed
            executeMultiByteCommand = command;
            break;
        case REPORT_ANALOG:
        case REPORT_DIGITAL:
            waitForData = 1; // two data bytes needed
            executeMultiByteCommand = command;
            break;
        case SYSTEM_RESET:
            systemReset();
            break;
        case REPORT_VERSION:
            Firmata.printVersion();
            break;
        }
    }
}



//------------------------------------------------------------------------------
// Serial Send Handling

// send an analog message
void FirmataClass::sendAnalog(byte pin, int value) 
{
	// pin can only be 0-15, so chop higher bits
	Serial.print(ANALOG_MESSAGE | (pin & 0xF), BYTE);
	Serial.print(value % 128, BYTE);
	Serial.print(value >> 7, BYTE); 
}

// send a single digital pin in a digital message
void FirmataClass::sendDigital(byte pin, int value) 
{
	// TODO add single pin digital messages to the  protocol
}

// send 14-bits in a single digital message
void FirmataClass::sendDigitalPortPair(byte port, int value) 
{
	// TODO: the digital message should not be sent on the serial port every
	// time sendDigital() is called.  Instead, it should add it to an int
	// which will be sent on a schedule.  If a pin changes more than once
	// before the digital message is sent on the serial port, it should send a
	// digital message for each change.
 
	// TODO: some math needs to happen for pin > 14 since MIDI channels are used
	Serial.print(DIGITAL_MESSAGE | (port & 0xF),BYTE);
	Serial.print(value % 128, BYTE); // Tx pins 0-6
	Serial.print(value >> 7, BYTE);  // Tx pins 7-13
}

// send a single digital pin in a digital message
void FirmataClass::sendSysex(byte command, byte bytec, byte* bytev) 
{
    byte i;
    Serial.print(START_SYSEX, BYTE);
    Serial.print(command, BYTE);
    for(i=0; i<bytec; i++) {
        Serial.print(bytev[i], BYTE);        
    }
    Serial.print(END_SYSEX, BYTE);
}


// Internal Actions/////////////////////////////////////////////////////////////

// generic callbacks
void FirmataClass::attach(byte command, callbackFunction newFunction)
{
    // TODO this should be a big switch() or something better... hmm
    switch(command) {
    case ANALOG_MESSAGE: currentAnalogCallback = newFunction; break;
    case DIGITAL_MESSAGE: currentDigitalCallback = newFunction; break;
    case REPORT_ANALOG: currentReportAnalogCallback = newFunction; break;
    case REPORT_DIGITAL: currentReportDigitalCallback = newFunction; break;
    case SET_PIN_MODE:currentPinModeCallback = newFunction; break;
    }
}
void FirmataClass::detach(byte command)
{
    attach(command, NULL);
}

// sysex callbacks
/*
 * this is too complicated for analogReceive, but maybe for Sysex?
 void FirmataClass::attachSysexReceive(sysexFunction newFunction)
 {
 byte i;
 byte tmpCount = analogReceiveFunctionCount;
 analogReceiveFunction* tmpArray = analogReceiveFunctionArray;
 analogReceiveFunctionCount++;
 analogReceiveFunctionArray = (analogReceiveFunction*) calloc(analogReceiveFunctionCount, sizeof(analogReceiveFunction));
 for(i = 0; i < tmpCount; i++) {
 analogReceiveFunctionArray[i] = tmpArray[i];
 }
 analogReceiveFunctionArray[tmpCount] = newFunction;
 free(tmpArray);
 }
*/

//******************************************************************************
//* Private Methods
//******************************************************************************



// resets the system state upon a SYSTEM_RESET message from the host software
void FirmataClass::systemReset(void)
{
    byte i;

    waitForData = 0; // this flag says the next serial input will be data
    executeMultiByteCommand = 0; // execute this after getting multi-byte data
    multiByteChannel = 0; // channel data for multiByteCommands
    for(i=0; i<MAX_DATA_BYTES; i++) {
        storedInputData[i] = 0;
    }

    currentAnalogCallback = NULL;
    currentDigitalCallback = NULL;
    currentReportAnalogCallback = NULL;
    currentReportDigitalCallback = NULL;
    currentPinModeCallback = NULL;

    // TODO empty serial buffer here
}



// =============================================================================
// used for flashing the pin for the version number
void FirmataClass::pin13strobe(int count, int onInterval, int offInterval) 
{
    byte i;
    pinMode(VERSION_BLINK_PIN, OUTPUT);
    for(i=0; i<count; i++) {
        delay(offInterval);
        digitalWrite(VERSION_BLINK_PIN, HIGH);
        delay(onInterval);
        digitalWrite(VERSION_BLINK_PIN, LOW);
    }
}


// make one instance for the user to use
FirmataClass Firmata;