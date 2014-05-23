CC = gcc
CFLAGS += -g -Wall -O0
OBJS = hello_world.o

# compile everything; this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile.
all: hello_world FORCE

hello_world: $(OBJS) FORCE
	$(CC) $(CFLAGS) -o hello_world $(OBJS)

%.o: %.c FORCE
	$(CC) $(CFLAGS) -c -std=c99 $<

clean: FORCE
	/bin/rm -f *.o *~ hello_world

FORCE:
