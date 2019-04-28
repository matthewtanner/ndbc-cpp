LIBDIR		:= lib
TESTDIR		:= test
LIBTGT		:= $(LIBDIR)/libcbuoy.a
TESTTGT		:= $(TESTDIR)/cbuoy-dump
TESTINCS    := -I$(LIBDIR)
TESTLIBS    := -L$(LIBDIR) -lcbuoy -lcurl
CC			:= g++
CFLAGS		:= -Wall

all: $(TESTTGT) $(LIBTGT)
test: $(TESTTGT)
lib: $(LIBTGT)

$(TESTTGT): $(LIBTGT)
	$(CC) $(CFLAGS) $(TESTINCS) $(TESTTGT).cpp $(TESTLIBS) -o $(TESTTGT)

$(LIBTGT): NdbcBuoy.o
	ar rcs $(LIBTGT) $(LIBDIR)/NdbcBuoy.o

NdbcBuoy.o: 
	$(CC) $(CFLAGS) -c $(LIBDIR)/NdbcBuoy.cpp -o $(LIBDIR)/NdbcBuoy.o

clean:
	rm -f $(LIBDIR)/*.o
	rm -f $(LIBTGT)
	rm -f $(TESTDIR)/*.o
	rm -f $(TESTTGT)
