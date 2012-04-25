# Ndless bFLT loader toolchain

A toolchain that integrates with Ndless that allows compiling executables for running on Ndless bFLT loader (https://github.com/tangrs/ndless-bflt-loader).

## Status

* Shared library support working with workarounds (TODO: fix)
* Data section relocations are working
* Text section relocations are not working

## Toolchain setup

Firstly you need binutils compiled for ARM. Get your binutils from your favourite location.

It's best to let binutils have it's own build directory. ```mkdir binutils-build && cd binutils-build```

```../binutils-src/configure --prefix=/usr/local --target=arm-none-eabi --disable-nls``` and ```make```

Note that you don't actually need to install it. Make a note of the location of the build directory and original source directory.

Next, checkout the source code for elf2flt.

Log into the CVS ```cvs -d:pserver:anonymous@cvs.uclinux.org:/var/cvs login```

Press Enter with no password entered.

Then checkout the source code ```cvs -z3 -d:pserver:anonymous@cvs.uclinux.org:/var/cvs checkout -P elf2flt```

Change into the elf2flt directory and run

```
./configure --target=arm-none-eabi \
--prefix=/usr/local \
--with-libbfd=/path/to/binutils/src/build/directory/libbfd.a \
--with-libiberty=/path/to/binutils/build/directory/libiberty/libiberty.a \
--with-bfd-include-dir=/path/to/binutils/build/directory/bfd \
--with-binutils-include-dir=/path/to/binutils/src/include
```

Replace ```/path/to/binutils/build/directory``` with the path to your build directory and ```/path/to/binutils/src``` with the original binutils source code directory. You may also want to change the prefix if you installed your toolchain elsewhere.

Run ```make``` and ```sudo make install``` and you'll have a working elf2flt toolset.

Finally you need to change into the ```tools``` directory and run ```make```. This will build the nessecary startup files.

To output bFLT executables for your projects, you simply need to change your ```GCC``` and ```LD``` to ```nspire-bflt-gcc``` and ```nspire-bflt-ld``` respectively. You also need to remove the call to ```objcopy```.

The output from ```nspire-bflt-ld``` will be the executable itself.

Here's a sample Makefile

```
GCC = nspire-bflt-gcc
LD = nspire-bflt-ld
GCCFLAGS = -Wall -W
LDFLAGS =
EXE = test.bflt.tns
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
vpath %.tns $(DISTDIR)

all: $(EXE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<
%.o: %.S
	$(GCC) $(GCCFLAGS) -c $<

$(EXE): $(OBJS)
	$(LD) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o *.gdb a.out
	rm -f $(EXE)
```

## License

See the LICENSE file in each folder to see what the files in that folder are licensed under. The file header also indicates the license used for that particular file.

Any unmarked file is licensed under the Mozilla Public License.