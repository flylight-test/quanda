#ifndef LOGSUTILS_H
#define LOGSUTILS_H

//Path vers fichier de logs
#define LOGPATH "/cygdrive/c/Users/fsiga/Desktop/OS_I2/fichiers/Logs/logs"

//Prototypes logs
void write_logs(char *buf, char *path);
char *current_time();
char *getCurrentPath(char const *file, char const *function, int const line);

#endif