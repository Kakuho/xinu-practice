/* xsh_sleep.c - xsh_sleep */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * Spawns a Producer Consumer problem
 *------------------------------------------------------------------------
 */

void sndch(char ch);

shellcmd sharedAB(int nargs, char *args[])
{
  resume( create(sndch, MINSTK, 20, "process sndch(A)", 1, 'A') );
  resume( create(sndch, MINSTK, 20, "process sndch(B)", 1, 'B') );
  printf("sharedAB has died");
}

void sndch(char ch){
  while(1)
    putc(CONSOLE, ch);
}
