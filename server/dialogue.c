#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"
#include "logsUtils.h"


DIALOGUE *stock_dialogue(char *filePath)
{
    char ligne[264];
    int index=0;

    DIALOGUE *dialogue=NULL;
    dialogue = malloc(line_number(filePath)*sizeof(DIALOGUE));

    if(dialogue==NULL)
    {
        write_logs("Erreur d'allocation mémoire à la récupération des questions/réponses dans le fichier",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        FILE *file = NULL;
        file = fopen(filePath,"r+");

        if(file == NULL)
        {
            write_logs("Erreur lors de l'ouverture du fichier de questions/réponses (Function stock_dialogue))",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
            exit(EXIT_FAILURE);
        }
        else
        {
            while(fgets(ligne,sizeof(ligne),file) != NULL)
            {
                strcpy(dialogue[index].question,strtok(ligne,";"));
                strcpy(dialogue[index].reponse,strtok(NULL,";"));
            }
            fclose(file);

            return dialogue;
        }
    }
}

int line_number(char *filePath)
{
    char ligne[300];
    int lignes=0;
    FILE *file = NULL;
    file=fopen(filePath,"r+");

    if(file == NULL)
    {
        write_logs("Erreur lors de l'ouverture du fichier de questions/réponses (Function line_number())",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        while(fgets(ligne,sizeof(ligne),file) != NULL)
        {
            lignes++;
        }
        fclose(file);

        return lignes;
    }
}