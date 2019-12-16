CC=gcc
FLAGS= -Wall
EXE=client

all : $(EXE) clean echo

$(EXE) : client.o color.o logsUtils.o scan.o
	$(CC) -o $@ $^

client.o : client.c scan.h color.h logsUtils.h
	$(CC) -o $@ -c $< $(FLAGS)

scan.o : scan.c
	$(CC) -o $@ -c $< $(FLAGS)

color.o : color.c
	$(CC) -o $@ -c $< $(FLAGS)

logsUtils.o : logsUtils.c
	$(CC) -o $@ -c $< $(FLAGS)

clean :
	rm -rf *.o

echo:
	$(info Compilation terminée)



