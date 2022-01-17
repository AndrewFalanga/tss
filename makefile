.PHONY: all clean

all: tss tssc

tss: tss.o tss_func.o

tssc: tssc.o tss_func.o

clean:
	$(RM) *.o tss tssc
