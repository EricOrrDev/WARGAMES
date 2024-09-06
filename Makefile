.DEFAULT_GOAL := all
TARGET = WARGAMES-V4
CC = gcc
CFLAGS = -Wall -O2
DFLAGS = -g -Wall

#OBJECT FILES
oldprint.o : oldprint.h oldprint.c
	$(CC) $(DFLAGS) -c oldprint.c

interactive.o : oldprint.h game.h interactive.h interactive.c

	$(CC) $(DFLAGS) -c interactive.c
game.o : oldprint.h game.h game.c
	$(CC) $(DFLAGS) -c game.c

credits.o : oldprint.h credits.c 
	$(CC) $(DFLAGS) -c credits.c

all : interactive.o game.o oldprint.o credits.o
	$(CC) $(CFLAGS) oldprint.o interactive.o game.o credits.o -o $(TARGET)

debug : interactive.o game.o oldprint.o credits.o
	$(CC) $(DFLAGS) oldprint.o interactive.o game.o credits.o -o $(TARGET)

clean :
	rm -f interactive.o oldprint.o game.o credits.o .GameLog $(TARGET)

packup :
	cd .. && tar --exclude-vcs -czvf $(TARGET).tar.gz $(TARGET)
