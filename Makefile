prefix = /usr/local

CC=gcc
CFLAGS=-Wall `pkg-config -cflags gtk4`
LDFLAGS= `pkg-config -libs gtk4`

all:
	$(CC) $(CFLAGS) -o ytdl ytdl.c $(LDFLAGS)
install:
	install ytdl $(DESTDIR)$(prefix)/bin

clean:
	rm -f ytdl
