#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void menu()
{
    printf("This is the main menu: \n");
    printf("\t1. Generate all the prime numbers smaller than a given n number \n");
    printf("\t2. Find the longest increasing contiguous subsequence of a given sequence \n");
    printf("\t0. Exit");
}

/// Checks if the given number is prime or not.
/// Returns 1 if the number is prime and 0 otherwise
short int prime(unsigned int n)
{
    if (n == 1 || n == 0 || (n%2 == 0 && n != 2))
        return 0;

    if (n == 2)
        return 1;

    for (unsigned int d = 3; d <= sqrt(n); d += 2)
        if (n%d == 0)
            return 0;

    return 1;
}

/// Function for the first assignment.
/// Prints all the prime numbers smaller than the number it reads from the keyboard
int primeNumbers()
{
    int n;
    printf("Give n: ");
    scanf_s("%d", &n);

    int i = 2;
    while (i < n)
    {
        if (prime(i) == 1)
            printf("%u, ", i);
        i++;
    }

    printf("\nDone!\n\n");
    return 0;
}

/// Finds and prints the longest contiguous subsequence of ascending-ordered numbers in the given array.
/// Receives the array and its length as parameters
int findAndPrintSubsequence(int* arr, unsigned short int n)
{
    unsigned short int maxL = 0, maxPos = 0, L = 0, pos = 0;
    // Find the searched subsequence
    for (unsigned short int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i-1])
            L++;
        else
        {
            if (maxL < L)
            {
                maxL = L;
                maxPos = pos;
            }
            pos = i;
            L = 0;
        }
    }

    if (maxL < L)
    {
        maxL = L;
        maxPos = pos;
    }

    // Print the found subsequence
    for (unsigned short int i = maxPos; i - maxPos <= maxL; i++)
        printf("%d, ", arr[i]);

    printf("Done!\n\n");
    return 0;
}

/// Function for the second assignment. Reads a sequence from the keyboard and
/// prints the longest contiguous ascending-ordered subsequence of elements it contains
int increasingSubsequence()
{
    int n = 0;
    printf("Please give the number of elements in the array: ");
    scanf_s("%d", &n);
    int arr[100];
    for (unsigned short int i = 0; i < n; i++)
    {
        printf("Give an element:");
        scanf_s("%d", &arr[i]);
    }
    findAndPrintSubsequence(arr, n);
    return 0;
}

int main()
{
    int finish = 0, command = -1;
    while (finish == 0)
    {
        menu();
        printf("\nPlease choose an option: ");
        scanf_s("%d", &command);
        switch (command)
        {
        case 1:
        {
            primeNumbers();
            break;
        }
        case 2:
        {
            increasingSubsequence();
            break;
        }
        case 0:
        {
            finish = 1;
            break;
        }
        default:
        {
            printf("Invalid command!\n\n");
            break;
        }
        }
    }
    printf("Goodbye! :)\n");
    system("pause");
    return 0;
}