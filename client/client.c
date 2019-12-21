// Client side
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <signal.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include "scan.h"
#include "color.h"
#include "logsUtils.h"
#include "filePid.h"

#define PUBLIC_FIFO "../fichiers/PUBLIC/fifo"
#define PRIVATE "../fichiers/PRIVATE"

void deletMyPidFromFile();
int serverIsRunning();
  
int main() 
{ 
    /* CTR+C => Unlink its private fifo and delet its pid from file */
    signal(SIGINT,deletMyPidFromFile);
    
    if(serverIsRunning())
    {
   
        int public_descriptor=-1; 
        int private_descriptor=-1;
        char userQuestion[126]={0};
        char serverResponse[126]={0};
        char private_fifo[126]={0};
        char pidAndQuestion[256]={0};

        /* Create a unique PRIVATE fifo for the current client */
        sprintf(private_fifo,"%s/%d",PRIVATE,getpid());
      
      
        /* Create the PRIVATE fifo */
        if((mkfifo(private_fifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != 0)
        {
            write_logs("Incapable de créer le PRIVATE FIFO (côté client)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
            exit(EXIT_FAILURE);
        }
        else
        {
            /* When created, add the PID of the client in a file */
            add(getpid());
                
            
                
            while (1)
            { 
                yellow();
                my_string_scanf(userQuestion,126);
                reset();
                sprintf(pidAndQuestion,"%d@%s",getpid(),userQuestion);

                if((public_descriptor=open(PUBLIC_FIFO, O_WRONLY)) < 0)
                {
                    green();
                    write_logs("Cannot access the public file descriptor, the server could have been interrupted ... Bye !",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                    unlink(private_fifo);
                    writeWithoutPid(getpid());
                    reset();
                    exit(EXIT_FAILURE);
                }
                else
                {
                    /* Write in the public descriptor */
                    write(public_descriptor, pidAndQuestion, strlen(pidAndQuestion)+1);
                        
                    close(public_descriptor);
                  
                    if((private_descriptor=open(private_fifo, O_RDONLY)) < 0)
                    {  
                        write_logs("Cannot access to the private file descriptor (client side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                        exit(EXIT_FAILURE);
                    } 
                    else
                    {
                        /* Read the server response in the private descriptor */
                        read(private_descriptor, serverResponse, sizeof(serverResponse));
                        red();
                        printf("[BOT]: %s\n", serverResponse);
                        reset();
                        close(private_descriptor);
                    }
                }  
            } 
        }
    }
    else
    {
        green();
        write_logs("The server is not currently running ..",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        reset();
        exit(EXIT_FAILURE);
    }
    return 0; 
}

void deletMyPidFromFile()
{
    /* Delet the private fifo */
    char fifoToDelet[256];
    sprintf(fifoToDelet,"%s/%d",PRIVATE,getpid());
    unlink(fifoToDelet);
    /* Delet the current pid from the file */
    writeWithoutPid(getpid());
    
    /* Leave the programme */
    signal(SIGINT,SIG_DFL);
    kill(getpid(),SIGINT);
}

int serverIsRunning()
{
    int serverIsRunning;
    
    if( access(PUBLIC_FIFO, F_OK) != -1)
    {
        serverIsRunning=1;
    }
    else
    {
        serverIsRunning=0;
    }
    return serverIsRunning;
}
