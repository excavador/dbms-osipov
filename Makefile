CC = gcc
CXX = g++
CFLAGS   = -shared -fPIC -Wall -Wextra -pedantic -O2
TARGET  = libdb.so
SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

doc:
	rst2html README.rst README.html

clean:
	rm -f *.o *.so

.PHONY : all
