#include <pthread.h>
#include <stdio.h>

#define COUNT 1000

typedef struct {
  int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
//
pthread_t threads[2];
threadParams_t threadParams[2];

// Unsafe global
int gsum = 0;

void *incThread(void *threadp) {
  int i;
  threadParams_t *threadParams = (threadParams_t *)threadp;

  for (i = 0; i < COUNT; i++) {
    gsum = gsum + i;
    fprintf(stderr, "Increment thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
  }
  return NULL;
}

void *decThread(void *threadp) {
  int i;
  threadParams_t *threadParams = (threadParams_t *)threadp;

  for (i = 0; i < COUNT; i++) {
    gsum = gsum - i;
    fprintf(stderr, "Decrement thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
  }
  return NULL;
}

int main() {
  int i = 0;

  threadParams[i].threadIdx = i;
  pthread_create(&threads[i],               // pointer to thread descriptor
                 (void *)0,                 // use default attributes
                 incThread,                 // thread function entry point
                 (void *)&(threadParams[i]) // parameters to pass in
  );
  i++;

  threadParams[i].threadIdx = i;
  pthread_create(&threads[i], (void *)0, decThread, (void *)&(threadParams[i]));

  for (i = 0; i < 2; i++)
    pthread_join(threads[i], NULL);

  printf("TEST COMPLETE\n");
}