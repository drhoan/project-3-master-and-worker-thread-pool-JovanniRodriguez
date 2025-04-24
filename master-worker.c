#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include <semaphore.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  buf_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t  buf_empty = PTHREAD_COND_INITIALIZER; //use locks instead of semaphores!!!
sem_t s;    

int item_to_produce, curr_buf_size;
int total_items, max_buf_size, num_workers, num_masters;

int *buffer;

void print_produced(int num, int master)
{

  printf("Produced %d by master %d\n", num, master);
}

void print_consumed(int num, int worker)
{

  printf("Consumed %d by worker %d\n", num, worker);
}

// produce items and place in buffer
// modify code below to synchronize correctly  ***********
void *generate_requests_loop(void *data)
{
  int thread_id = *((int *)data);

  while (1)
  {
    pthread_mutex_lock(&lock); //hold the lock
    if (item_to_produce >= total_items)
    {
      break;
    }

    buffer[curr_buf_size++] = item_to_produce;
    print_produced(item_to_produce, thread_id);
    item_to_produce++;
  }
  return 0;
}

// write function to be run by worker threads  ***************
// ensure that the workers call the function print_consumed when they consume an item

void *consume_items(void *data)
{
  int thread_id = *((int *)data);

  while(1)
  {
    pthread_mutex_lock(&lock);
    int num = buffer[curr_buf_size];

    print_consumed(num, thread_id);
  }

}

int main(int argc, char *argv[])
{
  sem_init(&s, 0, 1);    //init semaphore to 1
  int *master_thread_id;
  int *worker_thread_id;
  pthread_t *master_thread;
  pthread_t *worker_thread;
  item_to_produce = 0;
  curr_buf_size = 0;

  int i;

  if (argc < 5)
  {
    printf("./master-worker #total_items #max_buf_size #num_workers #masters e.g. ./exe 10000 1000 4 3\n");
    exit(1);
  }
  else
  {
    num_masters = atoi(argv[4]);
    num_workers = atoi(argv[3]);
    total_items = atoi(argv[1]);
    max_buf_size = atoi(argv[2]);
  }

  buffer = (int *)malloc(sizeof(int) * max_buf_size);

  // create master producer threads
  master_thread_id = (int *)malloc(sizeof(int) * num_masters);
  master_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_masters);
  for (i = 0; i < num_masters; i++)
    master_thread_id[i] = i;

  for (i = 0; i < num_masters; i++)
    pthread_create(&master_thread[i], NULL, generate_requests_loop, (void *)&master_thread_id[i]);

  // create worker consumer threads **************

  worker_thread_id = (int *)malloc(sizeof(int) * num_workers);
  worker_thread = (pthread_t *)malloc(sizeof(pthread_t) * num_workers);
  for (i = 0; i < num_workers; i++)
    worker_thread_id[i] = i;

  for (i = 0; i < num_workers; i++)
    pthread_create(&worker_thread[i], NULL, consume_items, (void *)&worker_thread_id[i]);

  // wait for all threads to complete
  for (i = 0; i < num_masters; i++)
  {
    pthread_join(master_thread[i], NULL);
    printf("master %d joined\n", i);
  }

  for (i = 0; i < num_workers; i++)
  {
    pthread_join(worker_thread[i], NULL);
    printf("worker %d joined\n", i);
  }

  /*----Deallocating Buffers---------------------*/
  free(buffer);
  free(master_thread_id);
  free(master_thread);

  return 0;
}
