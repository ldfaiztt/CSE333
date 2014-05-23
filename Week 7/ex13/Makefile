CFLAGS = -Wall -std=gnu++11 -g

ex13: ex13.o connect.o
	g++ $(CFLAGS) -o ex13 ex13.o connect.o

ex13.o: ex13.cc connect.h
	g++ $(CFLAGS) -c -o ex13.o ex13.cc

connect.o: connect.cc connect.h
	g++ $(CFLAGS) -c -o connect.o connect.cc

clean:
	/bin/rm -f *.o *~ ex13
