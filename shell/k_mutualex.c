#include <xinu.h>
#include <stdio.h>

// program to demonstrate 10 threads cooperating together in order to initialise an array

void workerthread(int32 index, int32* arr, sid32 mutex, sid32 buffer);
void outputthread(int* arr, sid32 buffer);

void mutual_cooperation(){
  sid32 mutex = semcreate(1);     // mutex for cooperating processes
  sid32 buffer = semcreate(-9);  // will be used as a barrier to the output thread 
  int32 arr[10];
  for(int32 i = 0; i < 10; i++){
    resume( create(workerthread, MINSTK, 20 + i, "workerthread", 4, i, arr, mutex, buffer));
  }
  resume( create(outputthread, MINSTK, 30 , "output thread", 2, arr, buffer));
}

void workerthread(int32 index, int32* arr, sid32 mutex, sid32 buffer){
  wait(mutex);
  arr[index] = index;
  signal(buffer);
  signal(mutex);
}

void outputthread(int* arr, sid32 buffer){
  printf("output thread wants to run :(\n");
  wait(buffer);
  for(int32 i = 0; i < 10; i++){
    printf("arr[%d] = %d\n", i, arr[i]);
  }
}
