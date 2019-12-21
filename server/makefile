CC=gcc
FLAGS= -Wall
EXE=server

all : $(EXE) clean echo

$(EXE) : server.o logsUtils.o traitement.o dialogue.o color.o scan.o filePid.o
	$(CC) -o $@ $^

server.o : server.c logsUtils.h traitement.h color.h scan.h filePid.h dialogue.h
	$(CC) -o $@ -c $< $(FLAGS)

logsUtils.o : logsUtils.c
	$(CC) -o $@ -c $< $(FLAGS)

traitement.o : traitement.c dialogue.h
	$(CC) -o $@ -c $< $(FLAGS)

dialogue.o : dialogue.c logsUtils.h
	$(CC) -o $@ -c $< $(FLAGS)

color.o : color.c
	$(CC) -o $@ -c $< $(FLAGS)
	
scan.o : scan.c
	$(CC) -o $@ -c $< $(FLAGS)
	
filePid.o : filePid.c dialogue.h
	$(CC) -o $@ -c $< $(FLAGS)

clean :
	rm -rf *.o

echo:
	$(info Compilation terminée)



