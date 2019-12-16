#ifndef STRUCTCLIENT_H
#define STRUCTCLIENT_H


/* STRUCTURE CLIENT */
typedef struct Client CLIENT;
struct Client
{
	int pid;
   	CLIENT *next_client;
};


/* TÊTE DE LISTE */
typedef struct Liste LISTE;
struct Liste
{
	CLIENT *first_client;
};

/* PROTOTYPES DES FONCTIONS DE MANIPULATION DE LA LISTE */
LISTE *init_client(int pid); //Retourne une liste de CLIENT dont le premier élément est le permier client
void insert_client_at_end(LISTE *liste, int pid); //Rajoute un client à la fin de la liste

#endif