# Arduino Test Process #
## Any one can make tests: ##
Test are created using the Arduino Test Suite library, and are developed as standard sketches.

Tests target to specific issues:
These tests can be attached to the issue reports. As issues are elimnated the test will be added to the listed of automated test runs.

Test suite coverage tests:
Tests designed to test the core functions and libraries. These are all version controlled and automatically run. These are submitted via pull requests to the main Arduino repository.

Certain tests must be passed before a new release can be made. That list is controlled by a version of the test plan identified by the release features and issues fixed.

Buildbot runs those tests any time code is changed in the master repository.