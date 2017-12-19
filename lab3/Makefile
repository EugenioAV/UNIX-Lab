CC = gcc
OBJECTS = message.o process.o

timer : $(OBJECTS)
	$(CC) $(OBJECTS) -o timer
message.o : message.c
	$(CC) -c message.c
process.o : process.c
	$(CC) -c process.c
check : check.c
	gcc check.c -o check
clean :
	rm -f timer $(OBJECTS)
	rm -f check check.o
