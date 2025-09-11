.PHONY: all clean

CFLAGS = -Wall
export CFLAGS

all:
	$(V)$(MAKE) -C src

clean:
	$(V)$(MAKE) -C src $@

$(V).SILENT:
