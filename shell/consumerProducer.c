#include <xinu.h>
#include <stdio.h>

/*--------------------------------------------------
 * Spawns Producer Consumer Problem
 * Should print 1, ... limit
 *--------------------------------------------------
 */

void Producer();
void Consumer();
int32 n = 0;
int32 limit = 1000;

void producerconsumer(){
  resume(create(Producer, MINSTK, 21, "producer", 0));
  resume(create(Consumer, MINSTK, 22, "consumer", 0));
}

void Producer(){
  for(int32 i = 1; i <= limit; i++){
    n++;
  }
}

void Consumer(){
  for(int32 i = 1; i <= limit; i++){
    printf("value of n = %d \n", n);
  }
}
