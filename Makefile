CC = gcc
CFLAGS = -Wall -Wextra -O2 -g 
SRC = src/main.c src/cpu_monitor.c src/memory_monitor.c src/disk_monitor.c src/network_monitor.c src/logger.c src/config_parser.c 
INCLUDE = include 
OUT = build/system_monitor

all:
	$(CC) $(CFLAGS) -I$(INCLUDE) $(SRC) -o $(OUT)

clean:
	rm -rf build/*
