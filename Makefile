all: libDisk.o
	gcc -o fakemain libDisk.o

libDisk.o: libDisk.c libDisk.h
	gcc -c libDisk.c