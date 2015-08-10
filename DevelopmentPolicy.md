# ATTENTION #
Please note that this page is out of date. Please refer to:
https://github.com/arduino/Arduino/wiki/Development-Policy

# Philosophy #

Arduino aims to make technology accessible and useful to new audiences such as artists, designers, or hobbyists.  The development efforts focus on that which allows people to get their work done.  To that end, it strives for the dual goals of simplicity (so people can actually use the platform) and robustness (so they create things that work).  It also attempts to provide a well-designed, maintainable, and stable platform for the future.

This means:

  * focusing on the official Arduino hardware
  * emphasizing API design
  * offering a small but easily-extendable core
  * sacrificing (when necessary) elegance of implementation for ease-of-use
  * emphasizing real use cases over theoretical possibilities
  * recognizing that documentation is as important as code
  * trying to get things right the first time (even if this takes longer)

but also accepting the inevitable presence of bugs, especially if they affect a small percentage of users and are easily worked around.

# Way to Contribute #

There are many ways to contribute to the Arduino development.  Please read the following suggestions to help make the process smooth and productive.

## Reporting Bugs ##

If you've found a bug in the Arduino software, please add it to the [issue tracker](http://code.google.com/p/arduino/issues/list).  The more specific you can be about the steps that lead to the problem, the better.  If the bug occurs in an Arduino sketch, try to find a minimal, self-contained piece of code that demonstrates the problem (and attach it).

If a bug has been reported in the forums, feel free to copy it into the issue tracker.  Summarize the issue and link to the original forum posting.

## Submitting Patches ##

When submitting patches, address a single issue.  Bug fixes should be kept separate from optimizations (which tend to be of lower priority) and API changes (which should be discussed before inclusion).  Match the indentation and style of the rest of the file.  Resist the temptation to rewrite an entire module while fixing a bug.  Don't make unrelated formatting changes elsewhere in the code.  Don't include a commented-out version of the previous version of the code.  Don't add a comment with your name and the date of changes.  The more changes you include in a patch, the more difficult it is to review and the less likely it is to be applied.

Please note that the Arduino core libraries support many boards and processors. When fixing or adding functionality for one of them, it's easy to break something on the others. Please test your changes on as many processors as possible. Even if you don't have a particular board, try compiling your patch for it to make sure that you haven't introduced any errors.

## Optimizing Code ##

Optimization tends to be a lower priority than bug fixes or new features, although performance is important for many situations.  Provide use cases for proposed optimizations and quantify the performance improvement achieved.  Remember that changes need to be tested on multiple microcontrollers and that maintainability of the code is important.

## Proposing Design Changes ##

Design changes (to the Arduino environment or core libraries) should be discussed on the developers mailing list.  Include use cases for the proposed change; these provide context and rationale.  Please discuss proposed changes before spending lots of time implementing them; it's much easier to adjust the design before the code is written.  We're unlikely to include changes we don't agree with, regardless of how much work you've put into them.

## Writing Libraries ##

Libraries are essential for extending the functionality of Arduino.  A few key libraries are maintained by the development team and included with the Arduino software distribution.  Many others are contributed by the community and listed on the [libraries page](http://arduino.cc/en/Reference/Libraries).  Writing a library is a great way to contribute to Arduino.  See [this tutorial](http://arduino.cc/en/Hacking/LibraryTutorial) for instructions.  If you've written a library, consider posting it to the developers mailing list for suggestions or possible inclusion in the list of contributed libraries.

## Writing Documentation ##

## Creating Examples ##

## Testing ##


# Tools #

## Source Code ##
The [Arduino source code](http://github.com/arduino/Arduino) is stored in a Git repository hosted by GitHub.  See BuildingArduino for instructions for getting and building the source.

## Developers Mailing List ##
The [developers mailing list](http://mail.arduino.cc/mailman/listinfo/developers_arduino.cc) (on arduino.cc) hosts discussions on the design of the Arduino development environment and the API for the core Arduino libraries.  Changes to either of these can be entered into the issue tracker, but should be discussed on the mailing list.  The list archives then serve as a history of the rationale behind the design decisions embodied in the software.

## Issue Tracking ##
The [issue tracker](http://code.google.com/p/arduino/issues/list) (hosted by Google Code) holds the list of individual items to be addressed in the Arduino software.  Straightforward tasks (e.g. bug fixes) can be entered in the issue tracker without separate discussion on the mailing list.  Design changes can be tracked there but should also be discussed on the developers mailing list.


# Relationship with Processing #

Arduino draws heavily on [Processing](http://processing.org/): in philosophy, in the API of the core libraries, and in the design and implementation of the development environment (IDE).  For functionality that exists in both Processing and Arduino, we follow Processing's lead in terms of design and implementation.  If you're looking to change something in Arduino that's already been updated in Processing, please take a look at what they've done first and, if possible, use their approach in Arduino as well.