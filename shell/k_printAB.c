/* printAB */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * Process with code WriteA prints A to console, similiar with WriteB
 *------------------------------------------------------------------------
 */

void WriteA();
void WriteB();

shellcmd printAB(int nargs, char *args[])
{
  resume( create(WriteA, MINSTK, 20, "process A", 0) );
  resume( create(WriteB, MINSTK, 20, "process A", 0) );
  printf("printAB has died");
}

void WriteA(){
  while(1)
    putc(CONSOLE, 'A');
}

void WriteB(){
  while(1)
    putc(CONSOLE, 'B');
}
