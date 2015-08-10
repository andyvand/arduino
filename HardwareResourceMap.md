# Introduction #

This page discusses the features of the microcontroller (ATmega) that are used by the Arduino functions.

# Global timer settings #
  * TIMER0, TIMER1, TIMER2: prescale factor = 64
  * On all chips other than ATMEGA8: TIMER0 in fast PWM mode
  * TIMER1, TIMER2 in 8-bit phase correct PWM mode
  * On ATMEGA1280:
    * TIMER3, TIMER4, TIMER5 prescale factor = 64
    * TIMER3, TIMER4, TIMER5 in 8-bit phase correct PWM mode

# Core functions #

pinMode();
  * Nothing significant

digitalWrite();
  * Nothing significant

digitalRead();
  * Nothing significant

analogRead();
  * Uses the ADC

analogReference();
  * Sets the ADC ref
  * ADC prescale factor = 128
  * ADC sample rate:
    * 125kHz on 16MHz boards
    * 62.5kHz on 8MHz boards


analogWrite();
  * Pins 5, 6 uses TIMER0
  * Pins 9, 10: uses TIMER1
  * Pins 3, 11 uses TIMER2
  * For the ATMEGA1280:
    * Pin 2: TIMER3B
    * Pin 3: TIMER3C
    * Pin 4: TIMER0B
    * Pin 5: TIMER3A
    * Pin 6: TIMER4A
    * Pin 7: TIMER4B
    * Pin 8: TIMER4C
    * Pin 9: TIMER2B
    * Pin 10: TIMER2A
    * Pin 11: TIMER1A
    * Pin 12: TIMER1B
    * Pin 13: TIMER0A
    * Pin 44: TIMER5C
    * Pin 45: TIMER5B
    * Pin 46: TIMER5A


Hardware Serial library:

> On the ATMEGA168 and 328:
    * USART0
    * USART\_RX\_vect

> On the ATMEGA8:
    * USART0
    * SIG\_UART\_RECV

> On the 1280 and 2560:
    * USART0, USART1, USART2, USART3,
    * SIG\_USART0\_RECV, SIG\_USART1\_RECV, SIG\_USART2\_RECV, SIG\_USART3\_RECV

millis();
  * TIMER0\_OVF\_vect

micros();
  * TIMER0\_OVF\_vect

delay();
  * TIMER0\_OVF\_vect (via millis())

delayMicroseconds();
  * Turns off all interrupts while it's running

pulseIn();
  * Nothing significant

shiftOut();
  * Nothing significant

attachInterrupt(intNum);
  * Enables the external interrupt
  * ATMEGA8, 168 and 328:
    * intNum = 0: uses INT0 on pin 2
    * intNum = 1: uses INT1 on pin 3

  * ATMEGA1280:
    * intNum = 0: uses INT4 on pin 2
    * intNum = 1: uses INT5 on pin 3
    * intNum = 2: uses INT0 on pin 21
    * intNum = 3: uses INT1 pin 20
    * intNum = 4:  INT2 on pin 19
    * intNum = 5 uses INT3 on pin 18.

detachInterrupt();
  * Disables the external interrupt


# Libraries #

EEPROM:
  * EEPROM

Ethernet:
  * Uses SPI
    * ATMEGA8, 168, 328: pins 13, 12, 11 and the ICSP header
    * ATMEGA1280: 50, 51, 52 and the ICSP header

Firmata:
> // Paging Hans Steiner...

Liquid Crystal:
  * Uses delayMicroseconds() in most functions, so will disable interrupts frequently

Matrix:
  * Nothing Significant

Servo:
  * ATMEGA8, 168, 328:
    * Uses TIMER1\_COMPA\_vect
    * Sets the prescale factor = 8 (normally = 64)
    * Uses OCR1A
  * ATMEGA1280:
    * everything same as others, plus
      * TIMER3, TIMER4, TIMER5,
      * TIMER3\_COMPA\_vect, TIMER4\_COMPA\_vect,TIMER5\_COMPA\_vect
      * OCR3A, OCR4A, OCR5A

Software Serial:
  * Uses delayMicroseconds() in most functions, so will disable interrupts frequently

Sprite:
  * Nothing Significant

Stepper:
  * uses 	TIMER0\_OVF\_vect via millis() function

Wire:
  * uses all the I2C resources
  * TWI frequency of 100kHz
  * activates internal pullups on clock and data pins