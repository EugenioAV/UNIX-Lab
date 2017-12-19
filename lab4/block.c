#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define _MULTI_THREADED

pthread_rwlock_t rwlock;

int compResults(char *string, int rc) {
  if (rc) {
    printf("Error in : %s, rc=%d", string, rc);
		return -1;
  }
	
	return 1;  
}

void *rdlockThread(void *arg)
{
  int rc;

  printf("Check lock for reading - ");
  rc = pthread_rwlock_rdlock(&rwlock);
	printf("rc = %d\n", rc);
  if (compResults("rdloc\n", rc)) printf("Ok\n");
	return NULL;
}

void *readData(void *arg)
{
  int rc;

  printf("Reading...\n");
  rc = pthread_rwlock_tryrdlock(&rwlock);
	printf("rc = %d\n", rc);
  if (compResults("read\n", rc)) printf("Ok\n");
	return NULL;
}



void *unlockThread(void *arg) {
	int rc;

	printf("Check unlock - ");
  rc = pthread_rwlock_unlock(&rwlock);
  if (compResults("unlock\n", rc)) printf("Ok\n");
	return NULL;
}

void *wrlockThread(void *arg)
{
  int rc;

  printf("Check lock for writing - ");
  rc = pthread_rwlock_wrlock(&rwlock);
  if (compResults("wrlock\n", rc)) printf("Ok\n");
	return NULL;
}

void *writeData(void *arg)
{
  int rc;

  printf("Writing...\n");
  rc = pthread_rwlock_trywrlock(&rwlock);
  if (compResults("wrlock\n", rc)) printf("Ok\n");
	return NULL;
}

int main(int argc, char **argv)
{
  int                   rc=0;
  pthread_t             thread, thread1;

  pthread_rwlock_init(&rwlock, NULL);

  pthread_create(&thread, NULL, wrlockThread, NULL);	
  pthread_create(&thread1, NULL, writeData, NULL);

	pthread_create(&thread, NULL, unlockThread, NULL);
	pthread_create(&thread1, NULL, writeData, NULL);
  
  rc = pthread_join(thread, NULL);
  rc = pthread_join(thread1, NULL);
  rc = pthread_rwlock_destroy(&rwlock);

  return 0;
}