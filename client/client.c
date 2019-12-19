// Client side
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <signal.h>
#include <stdbool.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include "scan.h"
#include "color.h"
#include "logsUtils.h"
#include <errno.h>

#define PUBLIC_FIFO "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PUBLIC/fifo"
#define PRIVATE "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PRIVATE"

void sendMessageToServerBeforeLeaving();
void sendMyPidToTheServer();
  
int main() 
{ 
	 signal(SIGINT,sendMessageToServerBeforeLeaving);

    int public_descriptor=-1; 
    int private_descriptor=-1;
    char userQuestion[126]={0};
    char serverResponse[126]={0};
    char private_fifo[126]={0};
    char pidAndQuestion[256]={0};

    /* Création du nom d'un unique fifo PRIVATE */
    sprintf(private_fifo,"%s/%d",PRIVATE,getpid());
  
  
    /* Création du fifo PRIVATE */
    if((mkfifo(private_fifo, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) != 0)
    {
        write_logs("Incapable de créer le PRIVATE FIFO (côté client)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Envoi du PID au serveur à la création du client */
       	sendMyPidToTheServer();

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
                reset();
                exit(EXIT_FAILURE);
            } 
            else
            {
                write(public_descriptor, pidAndQuestion, strlen(pidAndQuestion)+1);
                close(public_descriptor);
          
                if((private_descriptor=open(private_fifo, O_RDONLY)) < 0)
                {
                    write_logs("Cannot access to the private file descriptor (client side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
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

void sendMessageToServerBeforeLeaving()
{
	int public_descriptor = -1;
	char messageToServer[256]={0};
	
	if((public_descriptor=open(PUBLIC_FIFO, O_WRONLY)) < 0)
  	{	
  		green();
   		write_logs("Cannot access the public file descriptor, the server could have been interrupted ... Bye !",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
   		reset();
    	exit(EXIT_FAILURE);
 	} 
 	else
  	{
  		sprintf(messageToServer,"%d@%s",getpid(),"KillMePlease!");
  		write(public_descriptor, messageToServer, strlen(messageToServer)+1);
		close(public_descriptor);
	}

	green();
	printf("Private FIFO %d has been deleted ! Bye ..\n",getpid());
	reset();
	signal(SIGINT,SIG_DFL);
	kill(getpid(),SIGINT);
	exit(EXIT_SUCCESS);
}

void sendMyPidToTheServer()
{
	
  int public_descriptor = -1;
  if((public_descriptor=open(PUBLIC_FIFO, O_WRONLY)) < 0)
  {
    write_logs("The server is not running (client side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
    exit(EXIT_FAILURE);
  } 
	else
  {
    char pid[16];
    sprintf(pid,"%d@ThisIsMyPid!",getpid());
    write(public_descriptor, pid, strlen(pid)+1);
    close(public_descriptor);
  }
}