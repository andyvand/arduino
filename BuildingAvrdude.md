# ATTENTION #

this page is out of date please refer to:
https://github.com/arduino/Arduino/wiki/Building-avrdude-for-Arduino

# Mac OS X #

This was done on Mac OS X 10.7.1 (Lion) using Xcode 3.2.6 (installed in /Developer-old).

It seems that avrdude 5.11 needs, if you want usb support, libusb 0.1.12 or libusb 1.0.? with the libusb compat wrapper.  We use libusb-0.1.12 here.  Note that libusb-0.1.12 doesn't compile on 64-bit Mac OS X (some lines in the code assume 32-bit ints).

See also: http://developer.apple.com/library/mac/#documentation/Porting/Conceptual/PortingUnix/compiling/compiling.html and http://developer.apple.com/library/mac/#documentation/DeveloperTools/Conceptual/cross_development/Configuring/configuring.html

Building libusb 0.1.12:

```
./configure CC="/Developer-old/usr/bin/gcc" CPP="/Developer-old/usr/bin/cpp" CXX="/Developer-old/usr/bin/g++"  --disable-shared

make CFLAGS="-isysroot /Developer-old/SDKs/MacOSX10.5.sdk -arch ppc -mmacosx-version-min=10.4" LDFLAGS="-Wl,-syslibroot,/Developer-old/SDKs/MacOSX10.5.sdk -Wc,-arch,ppc -XCClinker -mmacosx-version-min=10.4" CXXFLAGS="-isysroot /Developer-old/SDKs/MacOSX10.5.sdk -arch ppc -mmacosx-version-min=10.4"

sudo make install

sudo mv /usr/local /usr/local-libusb-0.1.12-ppc

make clean

make CFLAGS="-isysroot /Developer-old/SDKs/MacOSX10.5.sdk -arch i386 -mmacosx-version-min=10.4" LDFLAGS="-Wl,-syslibroot,/Developer-old/SDKs/MacOSX10.5.sdk -Wc,-arch,i386 -XCClinker -mmacosx-version-min=10.4" CXXFLAGS="-isysroot /Developer-old/SDKs/MacOSX10.5.sdk -arch i386 -mmacosx-version-min=10.4"

sudo make install

for i in libusb.a libusbpp.a; do sudo lipo -create /usr/local/lib/$i /usr/local-libusb-0.1.12-ppc/lib/$i -output /usr/local/lib/$i; done
```


Building avrdude 5.11:

```
./configure CFLAGS="-I/usr/local/include -isysroot /Developer-old/SDKs/MacOSX10.5.sdk -mmacosx-version-min=10.4 -arch i386" LDFLAGS="-Wl,-L/usr/local/lib -Wl,-syslibroot,/Developer-old/SDKs/MacOSX10.5.sdk -Wl,-framework -Wl,IOKit -Wl,-framework -Wl,CoreFoundation -mmacosx-version-min=10.4 -Wl,-arch,i386" CC="/Developer-old/usr/bin/gcc"

make

mv avrdude avrdude-i386

make clean

# We lie to configure about our architecture so it works, then override the architecture to do the actual compilation.

./configure CFLAGS="-I/usr/local/include -isysroot /Developer-old/SDKs/MacOSX10.5.sdk -mmacosx-version-min=10.4 -arch i386" LDFLAGS="-Wl,-L/usr/local/lib -Wl,-syslibroot,/Developer-old/SDKs/MacOSX10.5.sdk -Wl,-framework -Wl,IOKit -Wl,-framework -Wl,CoreFoundation -mmacosx-version-min=10.4 -Wl,-arch,i386" CC="/Developer-old/usr/bin/gcc"

make CFLAGS="-I/usr/local/include -isysroot /Developer-old/SDKs/MacOSX10.5.sdk -mmacosx-version-min=10.4 -arch ppc" LDFLAGS="-L/usr/local/lib -Wl,-syslibroot,/Developer-old/SDKs/MacOSX10.5.sdk -Wl,-framework -Wl,IOKit -Wl,-framework -Wl,CoreFoundation -mmacosx-version-min=10.4 -arch ppc" CC="/Developer-old/usr/bin/gcc" 

mv avrdude avrdude-ppc

lipo -create avrdude-i386 avrdude-ppc -output avrdude
```



Building libusb 1.0.8 (http://www.libusb.org/wiki/libusb-1.0):

```
./configure CC="/Developer-old/usr/bin/gcc" CPP="/Developer-old/usr/bin/cpp"

make CFLAGS="-isysroot /Developer-old/SDKs/MacOSX10.5.sdk -arch ppc" LDFLAGS="-syslibroot /Developer-old/SDKs/MacOSX10.5.sdk -arch ppc"

sudo make install

# repeat for -arch i386 and -arch x86_64, moving previous one into its own directory first

sudo lipo -create /usr/local-libusb-ppc/lib/libusb-1.0.a /usr/local-libusb-i386/lib/libusb-1.0.a /usr/local-libusb-x86_64/lib/libusb-1.0.a -output /usr/local/lib/libusb-1.0.a

sudo lipo -create /usr/local-libusb-ppc/lib/libusb-1.0.0.dylib /usr/local-libusb-i386/lib/libusb-1.0.0.dylib /usr/local-libusb-x86_64/lib/libusb-1.0.0.dylib -output /usr/local/lib/libusb-1.0.0.dylib

# copy over other files (include/, pkgconfig/, libusb-1.0.la) and recreate symlink from libusb-1.0.dylib to libusb-1.0.0.dylib
```

# Windows #

Download libusb-win32 device bin (0.1.12.2): http://sourceforge.net/projects/libusb-win32/files/libusb-win32-releases/0.1.12.2/libusb-win32-device-bin-0.1.12.2.tar.gz/download

Copy:

libusb.a to /usr/local/lib
usb.h to /usr/local/include

To build avrdude:
```
./configure CFLAGS="-I /usr/local/include" LDFLAGS="-L /usr/local/lib -lusb"
```

Patch the Makefile:

```
351c351
< avrdude_LDADD = $(top_builddir)/$(noinst_LIBRARIES) -lusb   -lhid -lsetupapi -lm
---
> avrdude_LDADD = $(top_builddir)/$(noinst_LIBRARIES) -lusb   -lhid -lsetupapi
```

Run:

```
make
```