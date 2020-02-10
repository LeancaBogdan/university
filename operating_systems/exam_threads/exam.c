#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

unsigned int noOfVowels = 0;
unsigned int noOfConsonants = 0;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

void *f(void *param)
{
    char *word = (char*)param;
    for (unsigned int i = 0; i < strlen(word); i++)
    {
        if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
        {
            pthread_mutex_lock(&mtx1);
            noOfVowels++;
            pthread_mutex_unlock(&mtx1);
        }
        else
        {
            pthread_mutex_lock(&mtx2);
            noOfConsonants++;
            pthread_mutex_unlock(&mtx2);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        perror("Not enough parameters given!");
        exit(1);
    }

    pthread_t tid[argc];
    for (unsigned int i = 1; i < argc; i++)
    {
        if (pthread_create(tid + i - 1, NULL, f, argv[i]) < 0)
        {
            perror("Error creating thread!");
            exit(2);
        }
    }
    
    for (unsigned int i = 1; i < argc; i++)
    {
        pthread_join(tid[i-1], NULL);
    }
    printf("Vowels: %d\nConsonants: %d\n", noOfVowels, noOfConsonants);
    
    return 0;
}    

