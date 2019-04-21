CC			:= g++
CFLAGS		:= -Wall
EXEC		:= bdata
INCLUDE		:= 

all: /bin/$(EXEC)

/bin/$(EXEC): main.o BuoyDataFetcher.o
	$(CC) $(CFLAGS) $(INCLUDE) src/main.o src/BuoyDataFetcher.o -o bin/$(EXEC) -lcurl

main.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c src/main.cpp -o src/main.o 

BuoyDataFetcher.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c src/BuoyDataFetcher.cpp -o src/BuoyDataFetcher.o

clean:
	rm -f src/*.o
	rm -f bin/$(EXEC)
