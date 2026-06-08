GIT_TOP := $(shell git rev-parse --show-toplevel)
SRC_DIR := src
BUILD_DIR := build

VPATH = $(SRC_DIR)

.PHONY: debug release tss clean

all: npm
npm:
	@echo This will eventually be the build for the Networked Power Monitor

clean:
	@echo Cleaning up the build cruft
	$(RM) -r $(BUILD_DIR)

$(V).SILENT:
