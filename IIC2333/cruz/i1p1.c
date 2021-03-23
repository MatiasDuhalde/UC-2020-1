#include <stdio.h>
#include <unistd.h>
int main()
{
   fork();
   fork() && fork() || fork();
   fork();
 
   printf("forked %d\n", getpid());
   return 0;
}

