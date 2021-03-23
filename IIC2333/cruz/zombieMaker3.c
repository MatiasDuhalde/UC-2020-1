/* Source: http://www.amparo.net/ce155/fork-ex.html 

   Compile with:
     gcc -o fork fork.c

   Run (in Unix/Linux/MacOSX) with:
     ./fork

*/

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */

int main() {
  pid_t pid;
  int nZombies = 3;
  int r, s;

  for(int i=0; i<nZombies; i++) {
    /* fork a child process */
    pid = fork();
    if (pid < 0) { 
      /* error occurred */
      fprintf(stderr, "Fork Failed"); 
      return 1;
    }
    else if (pid == 0) { 
      /* child process */
      printf("Child about to do exec\n"); 
      execlp("/bin/ls","ls",NULL);
      printf("Child done with exec\n");
    }
    else {
      /* parent */
      printf("Have my child become a zombie?\n");
      r = scanf("%d\n", &s);
    }
  }
  printf("Let's kill those zombies\n");
  for(int i=0; i<nZombies; i++) {
    wait(NULL);
  }
  printf("All children done!\n");

  return 0;
}

