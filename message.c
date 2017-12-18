#include "common.h"

void message(int signo) {
	if (signo == OK) {
		printf("The program completed successfully.\n");
	} else {
		if (signo == SIGALRM){
			count++;
			if (count == 1) {
				printf("The program will be closed after few seconds.\n");
			}
			if (count == 2) {
				printf("The program is closed forcibly.\n");
				kill(pid, SIGKILL);
			}
		}
	}
}
