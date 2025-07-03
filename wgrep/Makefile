CC = gcc
CFLAGS = -Wall -Werror
TARGET = wgrep
SOURCE = wgrep.c

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean