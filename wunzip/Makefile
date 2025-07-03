CC = gcc
CFLAGS = -Wall -Werror
TARGET = wunzip
SOURCE = wunzip.c

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean