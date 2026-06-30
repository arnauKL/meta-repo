CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2 

all: toccer

toccer: toccer.c
	$(CC) $(CFLAGS) toccer.c -o toccer

clean:
	rm -f toccer

install: all
	# cp -f toccer /usr/local/bin/toccer
	# chmod 755 /usr/local/bin/toccer
	cp -f toccer ~/.local/bin/toccer

uninstall:
	rm -f /usr/local/bin/toccer\

.PHONY: all clean dist install uninstall
