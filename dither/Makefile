CFLAGS = -Wall -Wextra -pedantic -std=c11
CC = cc
LDLIBS = -lm # stb_image.h needs it

default: dither.c
	$(CC) $(CFLAGS) dither.c -o dither $(LDLIBS)
