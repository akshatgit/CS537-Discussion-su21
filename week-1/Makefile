# CS537 SP2021 - DIS W2
#
# Example Makefile that builds a local library "example-lib" and then an
# application executable "example-app", which uses the library.
# credit: Guanzhou Hu


# This is the advanced version, showing much better automation.


CC=gcc
CFLAGS=-O2 -Wall -Werror
TARGET=example-app

# Use helper functions to "search" for files here.
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))


.PHONY: all
all: $(TARGET)


$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CLIBS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS)


.PHONY: clean
clean:
	rm -f *.o $(TARGET)
	rm -f core