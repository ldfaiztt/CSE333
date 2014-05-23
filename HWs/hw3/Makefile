AR = ar
ARFLAGS = rcs
CC = gcc
CXX = g++
CFLAGS = -g -Wall -I. -I..
LDFLAGS = -L./libhw2 -lhw2 -L./libhw1 -lhw1
CPPUNITFLAGS = -L../gtest -lgtest -lpthread
HEADERS = test_fileindexutil.h fileindexutil.h \
          test_fileindexwriter.h fileindexwriter.h \
          test_fileindexreader.h FileIndexReader.h \
          test_hashtablereader.h HashTableReader.h \
          test_doctablereader.h DocTableReader.h \
          test_indextablereader.h IndexTableReader.h \
          test_docidtablereader.h DocIDTableReader.h \
          test_queryprocessor.h QueryProcessor.h

TESTOBJS = test_suite.o test_fileindexutil.o test_fileindexwriter.o \
           test_fileindexreader.o test_hashtablereader.o \
           test_doctablereader.o test_indextablereader.o \
           test_docidtablereader.o test_queryprocessor.o

OBJS = fileindexutil.o fileindexwriter.o FileIndexReader.o \
       IndexTableReader.o DocTableReader.o HashTableReader.o \
       DocIDTableReader.o QueryProcessor.o

all: buildfileindex filesearchshell test_suite libhw3.a

filesearchshell: filesearchshell.o libhw3.a $(HEADERS)
	$(CXX) $(CFLAGS) -o filesearchshell filesearchshell.o \
	-L. -lhw3 $(LDFLAGS)

buildfileindex: buildfileindex.o libhw3.a $(HEADERS)
	$(CXX) $(CFLAGS) -o buildfileindex buildfileindex.o \
	-L. -lhw3 $(LDFLAGS)

libhw3.a: $(OBJS) $(HEADERS)
	$(AR) $(ARFLAGS) libhw3.a $(OBJS)

test_suite: $(TESTOBJS) $(OBJS) $(HEADERS)
	$(CXX) $(CFLAGS) -o test_suite $(OBJS) $(TESTOBJS) \
	$(CPPUNITFLAGS) $(LDFLAGS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CFLAGS) -c $<

clean: FORCE
	/bin/rm -f *.o *~ test_suite libhw3.a buildfileindex \
        filesearchshell

FORCE:
