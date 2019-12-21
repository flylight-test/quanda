#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logsUtils.h"
#include "filePid.h"

int line_number()
{
	char ligne[300];
	int lignes=0;
	FILE *file= NULL;
	file=fopen(PATH_TO_PID,"r+");
	
	if(file == NULL)
	{
		write_logs("Error while trying to open the pid file",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
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
void add(int pid)
{
	char pids[8];
	FILE *file = NULL;
	file = fopen(PATH_TO_PID,"a");
	
	if(file == NULL)
	{
		write_logs("Error while trying to open the pid file",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
		exit(EXIT_FAILURE);
	}
	else
	{
		sprintf(pids,"%d\n",pid);
		fputs(pids,file);
		fclose(file);
	}
}

PID *readPid()
{
	PID *pids = NULL;
	pids=malloc(line_number()*sizeof(PID));
	
	if(pids==NULL)
	{
		write_logs("Malloc allocation error",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
		exit(EXIT_FAILURE);
	}
	else
	{
		FILE *file=NULL;
		file=fopen(PATH_TO_PID,"r+");
		
		if(file == NULL)
		{
			write_logs("Error while trying to open the pid file",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
			exit(EXIT_FAILURE);
		}
		else
		{
			char ligne[300];
			int i=0;
			while(fgets(ligne,sizeof(ligne),file) != NULL)
			{
				pids[i++].pid=atoi(ligne);
			}
			fclose(file);
		
			return pids;
		}
	}
}

void writeWithoutPid(int pid)
{
	PID *liste=readPid();
	int size=line_number();
	
	FILE *file=NULL;
	file=fopen(PATH_TO_PID,"w+");
	
	if(file == NULL)
	{
		write_logs("Error while trying to open the pid file",getCurrentPath(__FILE__,__FUNCTION__,__LINE__));
		exit(EXIT_FAILURE);
	}
	else
	{
		char pids[8];
		for(int i=0; i<size;i++)
		{
			if(liste[i].pid != pid)
			{
				sprintf(pids,"%d\n",liste[i].pid);
				fputs(pids,file);
			}
		}
		fclose(file);
	}
}
