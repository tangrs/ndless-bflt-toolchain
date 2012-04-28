GCC = nspire-bflt-gcc
GPP = nspire-bflt-g++
LD = nspire-bflt-ld
GCCFLAGS = -Wall -W
LDFLAGS = -nostdlib
EXE = test.bflt.tns
OBJS = main.o file1.o
vpath %.tns $(DISTDIR)

all: $(EXE)

%.o: %.cpp
	$(GPP) $(GCCFLAGS) -c $<
%.o: %.S
	$(GCC) $(GCCFLAGS) -c $<

$(EXE): $(OBJS)
	$(LD) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o *.gdb a.out
	rm -f $(EXE)