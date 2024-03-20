all: libDisk.o
	gcc -o fakemain libDisk.o

libDisk.o: libDisk.c
 libDisk.h
	gcc -c libDisk.c

CC = gcc
CFLAGS = -Wall -g
PROG = tinyFSDemo
OBJS = tinyFSDemo.o libTinyFS.o libDisk.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

tinyFsDemo.o: tinyFSDemo.c libTinyFS.h TinyFS_errno.h
	$(CC) $(CFLAGS) -c -o $@ $<

libTinyFS.o: libTinyFS.c linkedList.c libTinyFS.h libDisk.h libDisk.o TinyFS_errno.h
	$(CC) $(CFLAGS) -c -o $@ $<

libDisk.o: libDisk.c linkedList.c libDisk.h tinyFS.h TinyFS_errno.h
	$(CC) $(CFLAGS) -c -o $@ $<