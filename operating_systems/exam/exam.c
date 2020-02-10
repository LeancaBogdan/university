#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int nrApp[10];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *func(void *param)
{
    for (unsigned short int i = 0; i < strlen((char*)param); i++)
    {
        if (((char*)param)[i] >= '0' && ((char*)param)[i] <= '9')
        {
            unsigned short int digit = ((char*)param)[i] - '0';
            pthread_mutex_lock(&mtx);
            nrApp[digit]++;
            pthread_mutex_unlock(&mtx);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    for (unsigned short int i = 0; i <= 9; i++)
    {
        nrApp[i]=0;
    }

    if (argc < 3)
    {
        perror("Not enough arguments!");
        exit(1);
    }

    pthread_t tid[argc+1];
    for (unsigned short int i = 1; i < argc; i++)
    {
        if(pthread_create(&tid[i], NULL, func, argv[i]) < 0)
        {
            perror("Error creating thread!");
            exit(2);
        }
    }

    for (unsigned short int i = 1; i < argc; i++)
    {
        if (pthread_join(tid[i], NULL) < 0)
        {
            perror("Error joining thread!");
            exit(3);
        }
    }

    unsigned short int min = 100;
    unsigned short int minIndex = 0;
    for (unsigned short int i = 0; i <= 9; i++)
    {
        if (nrApp[i] < min && nrApp[i] > 0)
        {
            minIndex = i;
            min = nrApp[i];
        }
    }
    printf("The digit with the lowest number of appearances is %d\n", minIndex);
    return 0;
}

