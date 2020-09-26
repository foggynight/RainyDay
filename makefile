CC=g++
CFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=%.o)
PROG=rainy-day

all: $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm src/*.o

.PHONY: uninstall
uninstall:
	rm src/*.o $(PROG)
