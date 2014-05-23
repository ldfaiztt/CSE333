CFLAGS = -Wall -std=gnu++11 -g

ex14: ex14.o listenhandle.o
	g++ $(CFLAGS) -o ex14 ex14.o listenhandle.o

ex14.o: ex14.cc listenhandle.h
	g++ $(CFLAGS) -c -o ex14.o ex14.cc

listenhandle.o: listenhandle.cc listenhandle.h
	g++ $(CFLAGS) -c -o listenhandle.o listenhandle.cc

clean:
	/bin/rm -f *.o *~ ex14
