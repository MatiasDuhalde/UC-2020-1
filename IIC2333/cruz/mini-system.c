#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main () {
//  char command[50];
//   char command2[50];

// strcpy(command, "sleep 20; echo 1");
// strcpy(command2, "echo 2");
// system(command);
//   system(command2);
  system("sleep 20; echo 1");
  system("echo 2");
  printf("Soy el programa principal\n");

  return(0);
} 
