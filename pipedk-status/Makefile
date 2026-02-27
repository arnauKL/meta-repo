# Makefile for pipedk, custom stautsbar.
# variables
PROJECT = pipedk
SRCDIR = src
BINDIR_INSTALL = /usr/local/bin

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Default target
all: $(PROJECT)

# Create the executable
$(PROJECT): src/pipedk.c
	$(CC) $(CFLAGS) src/pipedk.c -o $@


.PHONY: all install uninstall clean distclean rebuild help

# Install the program
install: $(PROJECT)
	install -d $(BINDIR_INSTALL)
	install -m 755 $(PROJECT) $(BINDIR_INSTALL)

# Uninstall the program
uninstall:
	rm -f $(BINDIR_INSTALL)/$(PROJECT)

clean:
	rm $(PROJECT)

