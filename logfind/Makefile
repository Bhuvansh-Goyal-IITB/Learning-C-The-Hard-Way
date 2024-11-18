CC=gcc
INCDIRS=-I.
CFLAGS=-Wall -g $(OPTS) $(INCDIRS)

CFILES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(CFILES))

TARGET=bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

clean:
	rm -f *.o $(TARGET)
