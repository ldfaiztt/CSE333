# Copyright 2013 Chun-Wei Chen
# 1267040
# mijc0517@cs
# 07/05/13

CC = gcc
CFLAGS = -Wall -g -std=gnu99 -o
HEADERS = vector.h

all: ex5

ex5: ex5.o vector.o
	$(CC) $(CFLAGS) $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $@ -c $<

clean:
	rm -f *.o *~ ex5
