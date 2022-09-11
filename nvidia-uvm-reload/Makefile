CC = gcc
CFLAGS = -s -Wall -O3
BIN ?= $(PWD)/target

CFLAGS_DBUS = $(shell pkg-config --cflags --libs dbus-1)

default: $(BIN)/nvidia-uvm-reload
$(BIN)/nvidia-uvm-reload: *.c
	mkdir -p "$(BIN)"
	$(CC) $(CFLAGS) $< -o $@ $(CFLAGS_DBUS)

clean:
	rm -f $(BIN)/nvidia-uvm-reload

.PHONY: clean