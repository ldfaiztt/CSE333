CC = gcc
CFLAGS = -g -Wall
HEADERS = ll.h

all: example_ll_customer example_ll_of_ll

example_ll_customer: example_ll_customer.o ll.o
	$(CC) $(CFLAGS) example_ll_customer.o ll.o -o example_ll_customer

example_ll_of_ll: example_ll_of_ll.o ll.o
	$(CC) $(CFLAGS) example_ll_of_ll.o ll.o -o example_ll_of_ll

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean: FORCE
	/bin/rm -f *.o *~ example_ll_customer example_ll_of_ll

FORCE:
