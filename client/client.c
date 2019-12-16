// Client side
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include "scan.h"
#include "color.h"
#include "logsUtils.h"
#include <errno.h>

#define PUBLIC_FIFO "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PUBLIC/fifo"
#define PRIVATE "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PRIVATE"
  
int main() 
{ 
    int public_descriptor=-1; 
    int private_descriptor=-1;
    char userQuestion[126]={0};
    char serverResponse[126]={0};
    char private_fifo[126]={0};
    char pidAndQuestion[256]={0};

    //Création du nom d'un unique fifo PRIVATE
    sprintf(private_fifo,"%s/%d",PRIVATE,getpid());
  
  
    //Création du fifo PRIVATE
    if((mkfifo(private_fifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != 0)
    {
        write_logs("Incapable de créer le PRIVATE FIFO (côté client)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        while (1)
        { 
            yellow();
            my_string_scanf(userQuestion,126);
            reset();
            sprintf(pidAndQuestion,"%d@%s",getpid(),userQuestion);

            if((public_descriptor=open(PUBLIC_FIFO, O_WRONLY)) < 0)
            {
                write_logs("Incapable d'établir la connexion au descripteur de fichier (côté client)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                exit(EXIT_FAILURE);
            } 
            else
            {
                write(public_descriptor, pidAndQuestion, strlen(pidAndQuestion)+1);
                close(public_descriptor);
          
                if((private_descriptor=open(private_fifo, O_RDONLY)) < 0)
                {
                    write_logs("Incapable d'établir la connexion au descripteur de fichier (côté client)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                    exit(EXIT_FAILURE);
                } 
                else
                {
                    read(private_descriptor, serverResponse, sizeof(serverResponse));
                    red();
                    printf("[BOT]: %s\n", serverResponse);
                    reset();
                    close(private_descriptor);
                }
            }  
        } 
    }
    return 0; 
} 