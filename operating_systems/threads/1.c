// Implement a program that creates 2 threads. The threads will print their ID 10 times and then stop. Insure that the printed IDs always alternate.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// We initialize a mutex to be sure that the prints alternate.

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

// Function for the first thread, that repeats 10 times: lock the mutex, print the ID of the current thread, unlock the mutex.

void *f1(void *param)
{
    for (unsigned short int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mtx1);
        printf("Thread 1: %ld\n", pthread_self());
        pthread_mutex_unlock(&mtx1);
    }
    return NULL;
}

// Function for the second thread, that repeats 10 times: lock the mutex, print the ID of the current thread, unlock the mutex.

void *f2(void *param)
{
    for (unsigned short int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mtx1);
        printf("Thread 2: %ld\n", pthread_self());
        pthread_mutex_unlock(&mtx1);
    }
   return NULL;
}

// The main function, will create the threads and then wait for them to finish.
int main()
{
    // We declare the thread IDs of the threads to be created. 
    pthread_t t1, t2;

    // We create the first thread, with it's ID, the function f1 and no parameters, and validate it's creation.
    if (pthread_create(&t1, NULL, f1, NULL) != 0)
    {
        perror("Error creating thread 1!");
        exit(1);
    }

    // We create the second thread, with it's ID, the function f2 and no parameters, and validate it's creation.
    if (pthread_create(&t2, NULL, f2, NULL) != 0)
    {
        perror ("Error creating thread 2!");
        exit(2);
    }

    // We wait for the first thread to finish and validate it's finishing.
    if (pthread_join(t1, NULL) != 0)
    {
        perror("Error joining thread 1!");
        exit(3);
    }

    // We wait for the second thread to finish and validate it's finishing.
    if (pthread_join(t2, NULL) != 0)
    {
        perror("Error joining thread 2!");
        exit(4);
    }

    // If all went well, we exit the program with 0 (success).
    return 0;
}

