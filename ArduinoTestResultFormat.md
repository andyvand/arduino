# Arduino Test Result Format #

The Arduino test result format is based on the need for a result that can be streamed, summary data is at the end of the test, and is human readable. This format is equivalent to the Python Unit Test verbose mode 2. Details can be found here: http://docs.python.org/library/unittest.html

## Test result format description. ##

The file begins with info data. It's indicated by having "info." at the begging of the line.
### Common info fields: ###
```
info.MANUFACTURER    = Arduino
info.CPU-NAME        = ATmega328P
info.GCC-Version     = 4.3.2
info.AVR-LibC-Ver    = 1.6.4
info.Compiled-date   = Oct  4 2010
info.Test-Suite-Name = general
```

Followed by test run results.

### Test run results format: ###
```
name of test (information about test)   ... test result status
```

### A test has the following test result conditions: ###
```
ok
FAIL
ERROR
```

### Test result summary is last and separated from the test by dashes: ###
```
--------------------------
```
### Summary will say: ###
```
Ran n tests in Secs
```
### Test suite final condition: ###
```
OK
FAILED (failures=n)
```
### Example of Success: ###
```
info.MANUFACTURER    = Arduino
info.CPU-NAME        = ATmega328P
info.GCC-Version     = 4.3.2
info.AVR-LibC-Ver    = 1.6.4
info.Compiled-date   = Oct  5 2010
info.Test-Suite-Name = general
info.Free-memory     = 1464 bytes
DigitalReadWrite_02                                         ... ok
DigitalReadWrite_03                                         ... ok
DigitalReadWrite_04                                         ... ok
DigitalReadWrite_05                                         ... ok
DigitalReadWrite_06                                         ... ok
DigitalReadWrite_07                                         ... ok
DigitalReadWrite_08                                         ... ok
DigitalReadWrite_09                                         ... ok
DigitalReadWrite_10                                         ... ok
DigitalReadWrite_11                                         ... ok
DigitalReadWrite_12                                         ... ok
DigitalReadWrite_13                                         ... ok
DigitalReadWrite_14                                         ... ok
DigitalReadWrite_15                                         ... ok
DigitalReadWrite_16                                         ... ok
DigitalReadWrite_17                                         ... ok
DigitalReadWrite_18                                         ... ok
DigitalReadWrite_19                                         ... ok
PWMoutput_03  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_05  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_06  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_09  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_10  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_11  (PWM=128 50% LOW 49% HIGH)                    ... ok
AnalogInput_00 (Low=   0 High=1023 helper pin=15)           ... ok
AnalogInput_01 (Low=  15 High=1023 helper pin=14)           ... ok
AnalogInput_02 (Low=   0 High=1023 helper pin=17)           ... ok
AnalogInput_03 (Low=  15 High=1023 helper pin=16)           ... ok
AnalogInput_04 (Low=   0 High=1023 helper pin=19)           ... ok
AnalogInput_05 (Low=  14 High=1023 helper pin=18)           ... ok
--------------------------
Ran 30 tests in 6.362s

OK
```


### Example  Mixed Success and Fail Results: ###
```
info.MANUFACTURER    = Arduino
info.CPU-NAME        = ATmega328P
info.GCC-Version     = 4.3.2
info.AVR-LibC-Ver    = 1.6.4
info.Compiled-date   = Oct  4 2010
info.Test-Suite-Name = general
info.Free-memory     = 1464 bytes
DigitalReadWrite_02                                         ... ok
DigitalReadWrite_03                                         ... ok
DigitalReadWrite_04                                         ... ok
DigitalReadWrite_05                                         ... ok
DigitalReadWrite_06                                         ... ok
DigitalReadWrite_07                                         ... ok
DigitalReadWrite_08                                         ... ok
DigitalReadWrite_09                                         ... ok
DigitalReadWrite_10                                         ... ok
DigitalReadWrite_11                                         ... ok
DigitalReadWrite_12                                         ... ok
DigitalReadWrite_13                                         ... ok
DigitalReadWrite_14                                         ... ok
DigitalReadWrite_15                                         ... ok
DigitalReadWrite_16                                         ... ok
DigitalReadWrite_17                                         ... ok
DigitalReadWrite_18                                         ... ok
DigitalReadWrite_19                                         ... ok
PWMoutput_03  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_05  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_06  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_09  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_10  (PWM=128 50% LOW 49% HIGH)                    ... ok
PWMoutput_11  (PWM=128 50% LOW 49% HIGH)                    ... ok
AnalogInput_00 (Low=   0 High= 472 helper pin=15)           ... FAIL
AnalogInput_01 (Low= 477 High=1023 helper pin=14)           ... FAIL
AnalogInput_02 (Low=   0 High= 474 helper pin=17)           ... FAIL
AnalogInput_03 (Low= 479 High=1023 helper pin=16)           ... FAIL
AnalogInput_04 (Low=   0 High= 470 helper pin=19)           ... FAIL
AnalogInput_05 (Low= 475 High=1023 helper pin=18)           ... FAIL
--------------------------
Ran 30 tests in 7.326s

FAILED (failures=6)
```