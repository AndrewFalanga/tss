GIT_TOP := $(shell git rev-parse --show-toplevel)
SRC_DIR := src
BUILD_DIR := build

VPATH = $(SRC_DIR)

SRCS := tss.cpp
SRCS += tss_common.cpp
SRCS += tss_socket.cpp
SRCS += tssc.cpp

OBJS += $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

CPPFLAGS += -D_POSIX_C_SOURCE

CFLAGS += -std=c++17 -Wall -Werror
CFLAGS += -I$(SRC_DIR)

.PHONY: debug release tss clean

debug: CFLAGS += -ggdb -O0
debug: tss

release: CFLAGS += -O3
release: tss

tss: $(BUILD_DIR)/tss $(BUILD_DIR)/tssc

$(BUILD_DIR)/tss: $(filter-out $(BUILD_DIR)/tssc.o,$(OBJS))
	@echo Building $(@F)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/tssc: $(filter-out $(BUILD_DIR)/tss.o,$(OBJS))
	@echo Building $(@F)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJS): $(BUILD_DIR)

$(BUILD_DIR):
	@echo Build dir
	mkdir -p $@

$(BUILD_DIR)/%.o: %.cpp
	@echo Building $(@F) from $(<F)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning up the build cruft
	$(RM) -r $(BUILD_DIR)

$(V).SILENT:
