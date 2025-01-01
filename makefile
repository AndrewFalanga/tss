.PHONY: all clean

ifneq ($(V),)
override V :=
else
V=@
endif

CFLAGS = -Wall
export CFLAGS

all:
	$(V)$(MAKE) -C src

clean:
	$(V)$(MAKE) -C src $@
