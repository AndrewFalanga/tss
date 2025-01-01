.PHONY: all clean

CFLAGS += -std=c17 -D_POSIX_C_SOURCE -Wall -Werror

ifneq ($(V),)
override V :=
else
V=@
endif

debug: CFLAGS += -ggdb
debug: tss tssc

release: CFLAGS += -O3
release: tss tssc



tss: tss.o tss_common.o
	@echo Building $@
	$(V)$(CC) -o $@ $^ $(LDFLAGS)

tssc: tssc.o tss_common.o
	@echo Building $@
	$(V)$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@echo Building $@ from $<
	$(V)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning up the build cruft
	$(V)$(RM) *.o tss tssc
