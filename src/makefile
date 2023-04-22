.PHONY: all clean

CFLAGS += -std=c17 -D_POSIX_C_SOURCE

all: tss tssc

tss: tss.o tss_common.o

tssc: tssc.o tss_common.o

clean:
	$(RM) *.o tss tssc
