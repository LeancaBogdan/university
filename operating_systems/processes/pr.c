#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
//The wheel
//The main process (A) will create a subprocess (B) that will create another subprocess (C).
//Then the main process (A) will send a generated random number (between 1000 and 2000) to process B.
//The process (B) will subtract 10 units and will send the number to process (C). C will subtract
//20 units and will send the number to (A). The (A) process will subtract 30 units and will send the 
//number to (B), again. And so on, until the value is less than zero.
//In this moment, the game will stop. The winner is the process that estabilished the negative number.
//The communication between all the processes is done using pipe channels.

int main()
{
    int p1[2], p2[2], p3[2];                                //We initialize the pipes:
    pipe(p1);                                               //p1 between (A) and (B)
    pipe(p2);                                               //p2 between (B) and (C)
    pipe(p3);                                               //p3 between (C) and (A)
    pid_t idA = getpid();                                   //We store the pid of the parent process (A)
    int f = fork();                                         //We create the child process (B)
    if (f < 0)                                              //and we validate the creation
    {
        perror("Error creating process B!\n");
        exit(1);
    }
    if (f == 0)                                             //Child (B) context
    {
        int f2 = fork();                                    //We create the nephew process (C)      
        if (f2 < 0)                                         //and we validate the creation
        {
            perror("Error creating process C!\n");
            exit(2);
        }
        if (f2 == 0)                                        //Nephew (C) context
        {
            close(p1[0]);                                   //We close the unused pipe ends in (C)
            close(p1[1]);
            close(p2[1]);
            close(p3[0]);
            int randomC;                                    //Variable for storing the number in (C)
            if (read(p2[0], &randomC, sizeof(int)) < 0)     //Read the number from (B), validation of read
            {
                perror("Error reading in C!\n");
                exit(3);
            }
            while (randomC >= 0)                            
            { 
                printf("C: %d\n", randomC);
                randomC -= 20;
                if (randomC < 0)                            //Context: (C) is the winner
                {
                    printf("C is the winner! :)\n");        //We print that (C) is the winner
                    killpg(idA, SIGINT);                    //We kill all the processes that originate from A
                    exit(0);
                }
                if (write(p3[1], &randomC, sizeof(int)) < 0)//We write the obtained number in the pipe to (A), validation of write
                {
                    perror("Error writing in process C!\n");
                    exit(4);
                }
                if (read(p2[0], &randomC, sizeof(int)) < 0)//We read again, since we are in a while loop, from (B), with validation
                {
                    perror ("Error reading in C!\n");
                    exit(5);
                }
            }
        }
        close(p1[1]);                                       //We close the unused pipe ends in (B)
        close(p2[0]);
        close(p3[0]);
        close(p3[1]);
        int randomB;                                        //Variable for storing the number in (B)
        if (read(p1[0], &randomB, sizeof(int)) < 0)         //Read the number from (A), validation of read
        {
            perror("Error reading in B!\n");
            exit(4);
        }
        while (randomB >= 0)
        {
            printf("B: %d\n", randomB);
            randomB -= 10;
            if (randomB < 0)                                //Context: (B) is the winner
            {
                printf("B is the winner! \n");              //We print that (B) is the winner
                killpg(idA, SIGINT);                        //We kill all the processes that originate from A
                exit(0);
            }
            if (write(p2[1], &randomB, sizeof(int)) < 0)    //We write the obtained number in the pipe to (C), validation of write
            {
                perror("Error writing in process B!\n");
                exit(5);
            }
            if (read(p1[0], &randomB, sizeof(int)) < 0)     //We read again, since we are in a while loop, from (A), with validation
            {
                perror("Error writing in B!\n");
                exit(3);
            }
        }
    }
    close(p1[0]);                                           //We close the unused pipes in (A)
    close(p2[1]);
    close(p2[0]);
    close(p3[1]);
    srand(time(NULL));                                      //We give a seed to the rand() function
    int randomA = rand() % 1000 + 1000;                     //We generate a random number and fit it between 1000 and 2000
    if (write(p1[1], &randomA, sizeof(int)) < 0)            //We write the obtained number in the pipe to (B), validation of write
    {
        perror("Error writing in A!\n");
        exit(2);
    }
    if (read(p3[0], &randomA, sizeof(int)) < 0)             //We read the number from (C), validation of read
    {
        perror("Error reading in A!\n");
        exit(2);
    }
    while (randomA >= 0)                                    
    {
        printf("A: %d\n", randomA);
        randomA -= 30;
        if (randomA < 0)                                    //Context: (A) is the winner
        {
            printf("A is the winner! :)\n");                //We print that (A) is the winner
            killpg(getpid(), SIGINT);                       //We kill all the processes that originate from A
            return 0;
        }
        if (write(p1[1], &randomA, sizeof(int)) < 0)        //We write the obtained number in the pipe to (B), validation of write
        {
            perror("Error writing in A!\n");
            exit(2);
        }
        if (read(p3[0], &randomA, sizeof(int)) < 0)         //We read again, since we are in a while loop, from (C), with validation
        {
            perror("Error reading in A!\n");
            exit(2);
        }
    }
}

