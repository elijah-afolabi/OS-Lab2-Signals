/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int sigCounter = 0;
int handled = 0;

void handler(int signum)
{ //signal handler
  sigCounter += 1;
  handled = 1;
}

void printSeconds(int signum){
  printf("\nProgram ran for %d second(s).\n", sigCounter);
  exit(1);
}

int main(int argc, char * argv[])
{
  signal(SIGINT,printSeconds);
  while(1){
    signal(SIGALRM,handler); //register handler to handle SIGALRM
    alarm(1); //Schedule a SIGALRM for 1 second
    while(handled == 0); //busy wait for signal to be delivered
    handled = 0;
  }
  return 0; //never reached
}