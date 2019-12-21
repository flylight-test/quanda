#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scan.h"

//For the buffer overflow
void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//scanf() amelioration (stdin fgets() without \n at end and secured with a buffer overflow
int my_string_scanf(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        if(!strcmp(chaine,"\n")) strcpy(chaine," \n");
        if(!strcmp(chaine,"KillMePlease!\n")) strcpy(chaine," KillMePlease!\n");
        if(!strcmp(chaine,"ThisIsMyPid!\n")) strcpy(chaine," ThisIsMyPid!\n");
   
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            clearBuffer();
        }
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

// my_string_scanf() with atoi()
int my_int_scanf()
{
    char nombreTexte[100] = {0};

    if (my_string_scanf(nombreTexte, 100))
    {
        if( atoi(nombreTexte)>= 0)
        {
            return atoi(nombreTexte);
        }
        else // If there is a negatif number
        {
            return 0; 
        }
    }
    else
    {
        return 0;
    }
}
