CC = gcc
CFLAGS = -Wall -Werror
TARGET = wcat
SOURCE = wcat.c

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean