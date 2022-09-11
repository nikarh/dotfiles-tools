CC = gcc
CFLAGS = -s -Wall -O3
BIN ?= $(PWD)/target

default: $(BIN)/udev-monitor
$(BIN)/udev-monitor: *.c
	$(CC) $(CFLAGS) -o $@ $< -ludev

clean:
	rm -f $(BIN)/udev-monitor

.PHONY: clean