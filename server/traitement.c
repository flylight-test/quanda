#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dialogue.h"
#include "traitement.h"


SERVEUR traitement(char *pidAndQuestion)
{
    char question[128];
    SERVEUR traitement;
    traitement.client_pid=atoi(strtok(pidAndQuestion,"@"));;
    strcpy(question,strtok(NULL,"\0"));
    DIALOGUE *dialogue = NULL;
    int lignes=line_number(PATH_TO_QUESTIONS_RESPONSES);
    dialogue=stock_dialogue(PATH_TO_QUESTIONS_RESPONSES);


    strcpy(traitement.response,"Je ne connais pas la réponse à cette question...");

    for(int i=0 ; i<lignes ; i++)
    {
        if(!strcasecmp(question,dialogue[i].question))
        {
            strcpy(traitement.response,dialogue[i].reponse);
        }
    }
    return traitement;
}
