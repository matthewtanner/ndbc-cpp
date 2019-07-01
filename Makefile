LIBDIR		:= lib
TESTDIR		:= test
SRCDIR		:= src
INCDIR		:= include
LIBTGT		:= $(LIBDIR)/libcbuoy.a
TESTTGT		:= $(TESTDIR)/cbuoy-dump
INCLUDES    := -I$(SRCDIR) -I$(INCDIR)
TESTLIBS    := -L$(LIBDIR) -lcbuoy -lcurl
CC			:= g++
CFLAGS		:= -Wall

all: $(TESTTGT) $(LIBTGT)
test: $(TESTTGT)
lib: $(LIBTGT)

#### TODO use makefile variables here. To many hard-coded file names.

$(TESTTGT): $(LIBTGT)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTTGT).cpp $(TESTLIBS) -o $(TESTTGT)

$(LIBTGT): $(LIBDIR)/NdbcBuoy.o $(INCDIR)/NdbcBuoy.h
	ar rcs $(LIBTGT) $(LIBDIR)/NdbcBuoy.o

$(LIBDIR)/NdbcBuoy.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCDIR)/NdbcBuoy.cpp -o $(LIBDIR)/NdbcBuoy.o

clean:
	rm -f $(LIBDIR)/*.o
	rm -f $(LIBTGT)
	rm -f $(TESTDIR)/*.o
	rm -f $(TESTTGT)
