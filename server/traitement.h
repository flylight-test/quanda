#ifndef TRAITEMENT_H
#define TRAITEMENT_H



typedef struct Serveur SERVEUR;
struct Serveur
{
	int client_pid;
   	char response[128];
};

//Prototypes traitement
SERVEUR traitement(char *pidAndQuestion);

#endif