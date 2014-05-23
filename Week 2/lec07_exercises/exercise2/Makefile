CC = gcc
CFLAGS = -g -Wall
HEADERS = ll.h
AR = ar
ARFLAGS = rcs

all: example_ll_customer

example_ll_customer: example_ll_customer.o liblinkedlist.a
	$(CC) $(CFLAGS) example_ll_customer.o -o example_ll_customer \
	-L. -llinkedlist

liblinkedlist.a: ll.o
	$(AR) $(ARFLAGS) liblinkedlist.a ll.o

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean: FORCE
	/bin/rm -f *.o *.a *~ example_ll_customer

FORCE:
