#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scan.h"

//Pour éviter le buffer-overflow
void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//Version améliorée de scanf (fgets en stdin sans le \n à la fin -> remplacé par \0) et avec un nati buffer-overflow
int my_string_scanf(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        if(!strcmp(chaine,"\n")) strcpy(chaine," \n"); // Si la chaine est vide, on met un espace pour ne pas faire planter les algo de traitements
   
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

//Réutilise my_string_scanf() mais avec un atoi() pour convertir en int
int my_int_scanf()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (my_string_scanf(nombreTexte, 100)) // Si lecture du texte ok
    {
        if( atoi(nombreTexte)>= 0)
        {
            return atoi(nombreTexte);
        }
        else //Si le nombre est négatif, on renvoie 0 : Dans ce programme, aucune donnée ne peut être négative logiquement.
        {
            return 0; 
        }
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}
