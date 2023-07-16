.PHONY: all clean

CFLAGS = -Wall
export CFLAGS

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src $@
