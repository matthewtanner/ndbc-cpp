CC			:= g++
CFLAGS		:= -Wall
EXEC		:= bdata
INCLUDE		:= 

all: /bin/$(EXEC)

/bin/$(EXEC): main.o BuoyHandler.o
	$(CC) $(CFLAGS) $(INCLUDE) src/main.o src/BuoyHandler.o -o bin/$(EXEC) -lcurl

main.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c src/main.cpp -o src/main.o 

BuoyHandler.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c src/BuoyHandler.cpp -o src/BuoyHandler.o

clean:
	rm -f src/*.o
	rm -f bin/$(EXEC)
