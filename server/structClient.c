#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structClient.h"
#include "logsUtils.h"

LISTE *init_client(int pid)
{
    LISTE *liste=NULL;
    CLIENT *client=NULL;
    liste=malloc(sizeof(LISTE));
    client=malloc(sizeof(CLIENT));

    if((liste==NULL || client==NULL))
    {
        write_logs("Erreur d'allocation mémoire pour la liste chainée des clients (côté serveur)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        client->pid=pid;
        client->next_client=NULL;
        liste->first_client=client;

        return liste;
    }
}

void insert_client_at_end(LISTE *liste, int pid)
{
    CLIENT *new_client = NULL;
    new_client=malloc(sizeof(CLIENT));

    if(new_client==NULL)
    {
        write_logs("Erreur d'allocation mémoire pour la liste chainée des clients (côté serveur)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        new_client->pid=pid;
        new_client->next_client=NULL;

        CLIENT *going_at_end=liste->first_client;

        while(going_at_end->next_client!=NULL)
        {
            going_at_end=going_at_end->next_client;
        }
        going_at_end->next_client=new_client;
    }
}
