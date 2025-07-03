CC = gcc
CFLAGS = -Wall -Werror
TARGET = wzip
SOURCE = wzip.c

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean