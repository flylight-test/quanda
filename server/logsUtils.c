#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "logsUtils.h"


void write_logs(char *buf, char *path)
{
    puts(buf);
    FILE *file = NULL;
    file = fopen(LOGPATH, "a");
    if(file != NULL)
    {
    	fputs(current_time(),file);
        fputs(buf,file);
        fprintf(file," [ %s ]\n",path);
        fclose(file);
    }
    else
    {
        puts("Log error!");
    }
}

char *current_time()
{
    char *buf=malloc(sizeof(char)*32);
	time_t crt = time(NULL);
	strftime(buf, 32, "[%x - %X] ", localtime(&crt));
	return buf;
}

char *getCurrentPath(char const *file, char const *function, int const line)
{
    char *buffer=malloc(sizeof(char)*512);
    char path[256];

    sprintf(buffer,"Under : %s/%s in function %s (line %d)",getcwd(path,256),file,function,line);

    return buffer;
}
