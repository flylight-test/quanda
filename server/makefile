CC=gcc
FLAGS= -Wall
EXE=server

all : $(EXE) clean echo

$(EXE) : server.o logsUtils.o traitement.o dialogue.o structClient.o color.o
	$(CC) -o $@ $^

server.o : server.c logsUtils.h traitement.h structClient.h color.h
	$(CC) -o $@ -c $< $(FLAGS)

logsUtils.o : logsUtils.c
	$(CC) -o $@ -c $< $(FLAGS)

traitement.o : traitement.c dialogue.h
	$(CC) -o $@ -c $< $(FLAGS)

dialogue.o : dialogue.c logsUtils.h
	$(CC) -o $@ -c $< $(FLAGS)

color.o : color.c
	$(CC) -o $@ -c $< $(FLAGS)

clean :
	rm -rf *.o

echo:
	$(info Compilation terminée)



