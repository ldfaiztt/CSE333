# define the commands we will use for compilation and library building
AR = ar
ARFLAGS = rcs
CC = gcc
CXX = g++

# define useful flags to cc/ld/etc.
CFLAGS = -g -Wall -I. -I./libhw1 -I./libhw2 -I./libhw3 -I.. -O0 -std=gnu++0x
LDFLAGS = -L. -L./libhw1 -L./libhw2 -L./libhw3 -lhw4 -lhw3 -lhw2 -lhw1 -lpthread
CPPUNITFLAGS = -L../gtest -lgtest

# define common dependencies
OBJS =	ThreadPool.o ServerSocket.o HttpUtils.o HttpServer.o \
	HttpConnection.o FileReader.o

HEADERS = test_httpconnection.h HttpConnection.h \
	  HttpServer.h \
	  test_serversocket.h ServerSocket.h \
	  test_threadpool.h ThreadPool.h \
	  test_httputils.h HttpUtils.h \
	  HttpRequest.h HttpResponse.h \
	  test_filereader.h FileReader.h

TESTOBJS = test_httputils.o test_threadpool.o test_httpconnection.o \
	   test_filereader.o test_serversocket.o test_suite.o

# compile everything; this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile
all: http333d test_suite

http333d: http333d.o libhw4.a $(HEADERS)
	$(CXX) $(CFLAGS) -o http333d http333d.o \
	$(LDFLAGS)

libhw4.a: $(OBJS) $(HEADERS)
	$(AR) $(ARFLAGS) libhw4.a $(OBJS) 

test_suite: $(TESTOBJS) libhw4.a $(HEADERS)
	$(CXX) $(CFLAGS) -o test_suite $(TESTOBJS) \
	$(CPPUNITFLAGS) $(LDFLAGS) -lpthread

%.o: %.cc $(HEADERS)
	$(CXX) $(CFLAGS) -c $<

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -std=c99 $<

clean: FORCE
	/bin/rm -f *.o *~ test_suite http333d libhw4.a

FORCE:
