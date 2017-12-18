#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>

#define OK 1
pid_t pid;
int count;

void message(int signo);