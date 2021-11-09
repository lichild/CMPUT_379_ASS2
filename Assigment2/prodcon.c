/*
 * THe main function of prodcon
 * Author: Frank (Ziang) Li
 */

/* inculde libraries */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* macro defination */

// create a globle variable to change it in the threads
int g = 0;
// The function to be executed by all threads
void *myThreadFun(void *vargp) {
  // Store the value argument passed to this threads
  int *myid = (int *)vargp;

  // create a static variable to oberser its changes
  static int s = 0;

  // change static and globle varible
  ++s;
  ++g;

  printf("Thrread ID: %d, Static: %d, Gloable: %d\n", *myid, s, g);
}

/* main */
int main(int argc, char *argv[]) {

  /* init array for input */
  char str[10];

  /* log file id */
  int file_id = 0;

  /* get the # of consumers */
  if (argc == 1) {
    printf("You have to specify the number of threads to generate\n");
    exit(0);
  }
  if (argc > 3) {
    printf("Too much arguments, shoule be maximum 2.\n");
    exit(0);
  }
  int num_thread = atoi(argv[1]);

  /* the array to hold thread id */
  pthread_t id[num_thread];

  /* create threads */
  for (int i = 0; i < num_thread; i++) {
    pthread_create(&id[i], NULL, myThreadFun, (void *)&id[i]);
  }

  while (1) {
    fgets(str, 10, stdin);
    printf("%s\n", str);
    if (strcmp(str, "exit")) {
      break;
    }
  }

  return 0;
}
