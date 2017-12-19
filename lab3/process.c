#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

int main(int argc, char *argv[]) {
	count = 0;
	int status;
	struct itimerval tval;

	timerclear(&tval.it_interval);
	timerclear(&tval.it_value);
	
	tval.it_value.tv_sec = 3;
	tval.it_interval.tv_sec = 3;

	(void)signal(SIGALRM, message);
	
  switch(pid=fork()) {
  	case -1:
      perror("fork"); 
      exit(1);		  
			break;
  	case 0:
			execl(argv[1], argv[2], NULL);		
			break;
		default:
			(void)setitimer(ITIMER_REAL, &tval, NULL);
			waitpid(pid,&status, WUNTRACED);
			if (WIFEXITED(status) != 0) {
				message(OK);				
			}
	}
	(void)setitimer(ITIMER_REAL, NULL, NULL);
	return 0;
}