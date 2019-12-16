// Server side
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "logsUtils.h"
#include "traitement.h"
#include "structClient.h"

#define PUBLIC_FIFO "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PUBLIC/fifo"
#define PRIVATE "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/PRIVATE"
  
int main() 
{ 
    int private_descriptor=-1;
    int public_descriptor=-1;
    char clientPidAndQuestion[256]={0};
    char private_fifo[256];
    SERVEUR server ;
    LISTE *clientPidList=NULL ;
  
  	// Création du FIFO PUBLIC
  	unlink(PUBLIC_FIFO);
    if((mkfifo(PUBLIC_FIFO, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
    {
    	write_logs("Incapable de créer le FIFO PUBLIC (côté serveur)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
        exit(EXIT_FAILURE);
    }
    else
    {
    	while (1) 
	    { 
	        if((public_descriptor=open(PUBLIC_FIFO,O_RDONLY)) < 0)
	        {
	        	write_logs("Incapable d'établir la connexion au descripteur de fichier (côté serveur)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
                exit(EXIT_FAILURE);
	        }
	        else
	        {
	        	read(public_descriptor, clientPidAndQuestion, sizeof(clientPidAndQuestion));
		        close(public_descriptor);
		  		server=traitement(clientPidAndQuestion);
		  		if(clientPidList==NULL) clientPidList=init_client(server.client_pid);
		  		else insert_client_at_end(clientPidList, server.client_pid);
		  		sprintf(private_fifo,"%s/%d",PRIVATE,server.client_pid);

		        if((private_descriptor=open(private_fifo,O_WRONLY)) < 0)
		        {
		        	write_logs("Incapable d'établir la connexion au PRIVATE FIFO (côté serveur)",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
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
    return 0; 
}