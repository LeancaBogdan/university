#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>


int main()
{
    int p[2];
    pipe(p);

    int n;
    printf("Give n: ");
    scanf("%d", &n);
    if (n >= 100)
    {
        perror("Input number should be lower than 100! \n");
        exit(1);
    }

    write(p[1], &n, sizeof(int));

    int f = fork();
    if (f < 0)
    {
        perror("Error creating copy!\n");
        exit(1);
    }

    if (f == 0)
    {
        int n = 0;
        read(p[0], &n, sizeof(int));
        for (int i = 0; i < 10; i++)
        {
            int prod = n*(i+1);
            write(p[1], &prod, sizeof(int));
        }
        close(p[0]);
        close(p[1]);
        exit(0);
    }

    wait(0);
    for (int i = 0; i < 10; i++)
    {
        int prod;
        read(p[0], &prod, sizeof(int));
        printf("%d times %d is %d\n", n, i+1, prod);
    }
    close(p[0]);
    close(p[1]);
    
    return 0;
}

