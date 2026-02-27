TARGET = backfinder
CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11

all: $(TARGET)

$(TARGET): backfinder.c
	$(CC) $(CFLAGS) backfinder.c -o $(TARGET)

tag: tagfinder.c
	$(CC) $(CFLAGS) tagfinder.c -o tagfinder

index: tagindex.c
	$(CC) $(CFLAGS) tagindex.c -o tagindex

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
