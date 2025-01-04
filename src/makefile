.PHONY: all clean

CFLAGS += -std=c++17 -D_POSIX_C_SOURCE -Wall -Werror

debug: CFLAGS += -ggdb
debug: tss tssc

release: CFLAGS += -O3
release: tss tssc

tss: tss.o tss_common.o
	@echo Building $@
	$(CXX) -o $@ $^ $(LDFLAGS)

tssc: tssc.o tss_common.o
	@echo Building $@
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@echo Building $@ from $<
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning up the build cruft
	$(RM) *.o tss tssc

$(V).SILENT:
