// Server side
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <signal.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "logsUtils.h"
#include "color.h"
#include "traitement.h"
#include "structClient.h"

#define PUBLIC_FIFO "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PUBLIC/fifo"
#define PRIVATE "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PRIVATE"

/* CTR+C => Unlink the PUBLIC fifo and all the PRIVATE fifo, then leave */
void unlinkAllFifo();

/* Stock all the clients PID in this linked list */
LISTE *clientPidList=NULL ;

int main() 
{ 
	signal(SIGINT,unlinkAllFifo);

    int private_descriptor=-1;
    int public_descriptor=-1;
    char clientPidAndQuestion[256]={0};
    char private_fifo[256];
    SERVEUR server ;
  
  	
  	unlink(PUBLIC_FIFO);

    if((mkfifo(PUBLIC_FIFO, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
    {
    	write_logs("Cannot creat the PUBLIC fifo (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
    	while(1) 
	    { 
	        if((public_descriptor=open(PUBLIC_FIFO,O_RDONLY)) < 0)
	        {
	        	write_logs("Cannot connect to the public file descriptor (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                exit(EXIT_FAILURE);
	        }
	        else
	        {
	        	read(public_descriptor, clientPidAndQuestion, sizeof(clientPidAndQuestion));
		        close(public_descriptor);
		  		server=traitement(clientPidAndQuestion);
		  		/* If the client CTRL+C, we unlink its PRIVATE fifo */
		  		if(!strcasecmp(server.response,"NeedToKillThisPid"))
		  		{
		  			supprimer(clientPidList, server.client_pid);
		  			char delet_private_fifo[256];
		  			sprintf(delet_private_fifo,"%s/%d",PRIVATE,server.client_pid);
		  			unlink(delet_private_fifo);
		  		}
		  		/* When the client is created, we stock its PID in the linked list */
		  		else if(!strcasecmp(server.response,"NeedToSaveThisPid"))
		  		{
		  			if(clientPidList==NULL)
		  			{
		  				clientPidList=init_client(server.client_pid);
		  			}
		  			else
		  			{
		  				insert_client_at_end(clientPidList, server.client_pid);
		  			}
		  		}
		  		/* Otherwise, send a response to the client */
		  		else
		  		{
		  			/*
		  			if(clientPidList==NULL)
		  			{
		  				clientPidList=init_client(server.client_pid);
		  			}
		  			else
		  			{
		  				insert_client_at_end(clientPidList, server.client_pid);
		  			}
		  			*/

		  			sprintf(private_fifo,"%s/%d",PRIVATE,server.client_pid);

		        	if((private_descriptor=open(private_fifo,O_WRONLY)) < 0)
		        	{
		        		write_logs("Cannot connect to the private file descriptor (server side)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                		exit(EXIT_FAILURE);
		        	}
		        	else
		        	{
		        		write(private_descriptor, server.response, strlen(server.response)+1);
		        		close(private_descriptor);
		        	}
		  		}

	        }
	    } 
    }

    return 0; 
}

/* CTR+C => Unlink the PUBLIC fifo and all the PRIVATE fifo, then leave */
void unlinkAllFifo()
{
	unlink(PUBLIC_FIFO);
	char private_fifo[256];
	
	if(clientPidList != NULL && clientPidList->first_client != NULL)
	{
		CLIENT *going_at_end=clientPidList->first_client;

		sprintf(private_fifo,"%s/%d",PRIVATE,going_at_end->pid);
		unlink(private_fifo);
		green();
    	printf("Private fifo %d has been deleted !\n",going_at_end->pid);
    	reset();

   	 	while(going_at_end->next_client!=NULL)
    	{
    		sprintf(private_fifo,"%s/%d",PRIVATE,going_at_end->next_client->pid);
    		unlink(private_fifo);
    		green();
    		printf("Private fifo %d has been deleted !\n",going_at_end->next_client->pid);
    		reset();
    		going_at_end=going_at_end->next_client;
    	}
    }
    
    	
    signal(SIGINT,SIG_DFL);
    kill(getpid(),SIGINT);
    exit(EXIT_SUCCESS);
}