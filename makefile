# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2020 Robert Coffey

CC=g++
CFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=%.o)
PROG=rain

all: $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)


.SILENT: import
import:
	[ ! -d "olcPixelGameEngine" ] &&\
		git clone https://github.com/OneLoneCoder/olcPixelGameEngine;\
	[ ! -f "src/olcPixelGameEngine.h" ] &&\
		cp olcPixelGameEngine/olcPixelGameEngine.h src;\

.PHONY: clean
clean:
	rm -f src/*.o

.PHONY: uninstall
uninstall:
	rm -rf src/*.o src/olcPixelGameEngine.h olcPixelGameEngine $(PROG)
