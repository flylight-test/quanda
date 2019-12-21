
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
#include "filePid.h"
#include "traitement.h"
#include "dialogue.h"
#include "scan.h"

#define PUBLIC_FIFO "../fichiers/PUBLIC/fifo"
#define PRIVATE "../fichiers/PRIVATE"

void deletAllPidFromFile();
int serverIsNotRunning();

int main() 
{ 
    /* Can't handle more than one server*/
    if(serverIsNotRunning())
    {
	int bot;
    
	//Child process which is waitting for the client messages
	if((bot=fork())==0)
	{
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
			/* Read the client request */
			read(public_descriptor, clientPidAndQuestion, sizeof(clientPidAndQuestion));
			close(public_descriptor);
			server=traitement(clientPidAndQuestion);
		   
			/* Send a response to the client */
		    
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
	// Parent process which can create some new clients
	else
	{
	    char user_choice[3];
	
	    signal(SIGINT,deletAllPidFromFile);
	
	    while(1)
	    {
		green();
		puts("Do you wanna create a new client ? (y/n)");
		reset();
		white();
		my_string_scanf(user_choice,3);
		reset();
	    
		if(!strcmp(user_choice,"y\0"))
		{
		    int client;
		    if((client=fork())==0)
		    {
			execl("/usr/bin/xterm","xterm","-fa","fixed","-e","../client/client","client",NULL);
		    }
		    else
		    {	
			/* sleep(2) to make sure that the client has written his PID in the file before  reading it with readLast() */
			sleep(2);
			red();
			printf("Console launched with pid %d which launched the client with pid %d \n",client,readLast());
			reset();
		    }
		}
	    }
	}
    }
    else
    {
	green();
	write_logs("A server is already open",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
	reset();
	exit(EXIT_FAILURE);
    }
}

void deletAllPidFromFile()
{
    char fifoToDelet[256];
    PID * pids=readPid();

    /* Unlink all fifo */
    unlink(PUBLIC_FIFO);
    for(int i=0; i<line_number(PATH_TO_PID) ; i++)
    {
	sprintf(fifoToDelet,"%s/%d",PRIVATE,pids[i].pid);
	unlink(fifoToDelet);
    }
    
    /* Remove all pid from file */
    clearFile();
    
    /* Leave the program */
    signal(SIGINT,SIG_DFL);
    kill(getpid(),SIGINT);
}
int serverIsNotRunning()
{
    int serverIsNotRunning;

    if( access(PUBLIC_FIFO, F_OK) != -1)
    {
        serverIsNotRunning=0;
    }
    else
    {
        serverIsNotRunning=1;
    }
    return serverIsNotRunning;
}
