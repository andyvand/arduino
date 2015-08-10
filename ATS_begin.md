# ATS\_begin() #

## Description ##
Set the manufacture of the board, or shied that you would be testing the software for. Then set the test suite name. The function then initializes the beginning of the test process, enables serial, sets all the initial variables, and values.

## Syntax ##
ATS\_begin(manufName, testSuiteName)

## Parameters ##
manufName: manufacturer name, char array
testSuiteName: test suite name, char array

Returns
None

See also
[ATS\_end()](ATS_end.md)