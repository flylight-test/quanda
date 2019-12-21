#ifndef FILEPID_H
#define FILEPID_H

#define PATH_TO_PID "../fichiers/Pid/pid.txt"

typedef struct pidStruct PID;
struct pidStruct
{
	int pid;
};

void add(int pid);
PID *readPid();
void writeWithoutPid(int pid);
int line_number();

#endif
