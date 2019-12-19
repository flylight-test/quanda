#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#define PATH_TO_QUESTIONS_RESPONSES "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/QuestionsReponses/qr.txt"


typedef struct Serveur SERVEUR;
struct Serveur
{
	int client_pid;
   	char response[128];
};

//Prototypes traitement
SERVEUR traitement(char *pidAndQuestion);

#endif