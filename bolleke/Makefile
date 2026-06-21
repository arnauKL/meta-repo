CFLAGS = -Wall -Wextra -pedantic -std=c11

all: bol

$(TARGET): bol.c
	cc $(CFLAGS) bol.c -o bol

.PHONY: clean

clean:
	rm -f $(TARGET)
