#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
        write_logs("Malloc allocation error (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
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
    bool control=false;
    CLIENT *new_client = NULL;
    new_client=malloc(sizeof(CLIENT));

    if(new_client==NULL)
    {
        write_logs("Malloc allocation error (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        new_client->pid=pid;
        new_client->next_client=NULL;


        CLIENT *going_at_end=liste->first_client;
        if(going_at_end->pid==pid) control=true;

        while(going_at_end->next_client!=NULL)
        {
            if(going_at_end->next_client->pid==pid)
            {
                control=true;
            }
            going_at_end=going_at_end->next_client;
        }

        if(!control) going_at_end->next_client=new_client;
    }
}

void supprimer(LISTE* list, int pid)
{

    if (list == NULL)
    {
        write_logs("Clients list is empty (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }

    if (list->first_client != NULL)
    {
        if(list->first_client->pid == pid)
        {
            CLIENT *aSupprimer = list->first_client;
            list->first_client = list->first_client->next_client;
            free(aSupprimer);
        }
        else
        {
            CLIENT *move=list->first_client;

            while(move->next_client != NULL && move->next_client->pid!=pid)
            {
                move=move->next_client;
            }

            if(move->next_client != NULL)
            {
                CLIENT *aSupprimer = move->next_client;
                move->next_client = move->next_client->next_client;
                free(aSupprimer);
            }
        }
    }
}