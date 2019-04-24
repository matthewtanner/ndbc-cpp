CC			:= g++
CFLAGS		:= -Wall
EXEC		:= bdata
INCLUDE		:= 

all: /bin/$(EXEC)

/bin/$(EXEC): main.o NdbcBuoy.o
	$(CC) $(CFLAGS) $(INCLUDE) src/main.o src/NdbcBuoy.o -o bin/$(EXEC) -lcurl

main.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c src/main.cpp -o src/main.o 

NdbcBuoy.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c src/NdbcBuoy.cpp -o src/NdbcBuoy.o

clean:
	rm -f src/*.o
	rm -f bin/$(EXEC)
