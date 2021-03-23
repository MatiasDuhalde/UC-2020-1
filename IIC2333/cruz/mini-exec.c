#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main () {
   char command[] = "/bin/sleep";
   char *args[] = { "/bin/sleep", "20" };

   pid_t id = fork();
   if 
   execve("/bin/sleep", args, NULL);

   printf("Soy el programa principal y estoy esperando.\n");
   sleep(10);

   return(0);
} 
