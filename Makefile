CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Target directory (e.g. DIR=viewport-scaling)
DIR ?= .
CLEAN_DIR := $(patsubst %/,%,$(DIR))
NAME := $(notdir $(CLEAN_DIR))
ifeq ($(NAME),)
NAME := playground
endif
ifeq ($(NAME),.)
NAME := playground
endif

BUILD_DIR := $(CLEAN_DIR)/build
TARGET := $(BUILD_DIR)/$(NAME)

SRC := $(wildcard $(CLEAN_DIR)/*.c)
OBJ := $(patsubst $(CLEAN_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(TARGET)

ifeq ($(strip $(SRC)),)
$(TARGET):
	@echo "No C source files found in '$(CLEAN_DIR)'"
	@exit 1
else
$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
endif

$(BUILD_DIR)/%.o: $(CLEAN_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	cd $(CLEAN_DIR) && ./build/$(NAME)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean