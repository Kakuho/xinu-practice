/* xsh_sleep.c - xsh_sleep */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * Spawns a Producer Consumer problem
 *------------------------------------------------------------------------
 */

static int32 n = 0; // needs to be global otherwise cannot be shared between threads
static int32 limit = 2000;

void producer();
void consumer();

void producerconsumer()
{
  // we just need the ids, and not the actual value of the semaphore for waiting / signalling
  sid32 producedsem = semcreate(1);
  sid32 consumedsem = semcreate(0);
  resume (create(producer, MINSTK, 20, "producer", 2, producedsem, consumedsem) );
  resume (create(consumer, MINSTK, 21, "consumer", 2, producedsem, consumedsem) );
}

void producer(sid32 producedsem, sid32 consumedsem){
  for(int32 i = 0; i <= limit; i++){
    wait(consumedsem);
    n++;
    signal(producedsem);
  }
}

void consumer(sid32 producedsem, sid32 consumedsem){
  for(int32 i = 0; i <= limit; i++){
    wait(producedsem);
    printf("val: %d \n", n);
    signal(consumedsem);
  }
}
