#include <stdio.h>
#include <string.h>
#include "assert.h"
void sort(char s[50][10], int);

int Quicksort(void)
{
    int i;
    int n = 0;
    char s[50][10];


    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Failed to read a number\n");
        return 1;
    }
    if (n <= 0 || n > 50)
    {
        fprintf(stderr, "%d is out of the range 1..50\n", n);
        return 1;
    }
// Gobble rest of first line
    while ((i = getchar()) != EOF && i != '\n')
        ;

    for (i = 0; i < n; i++)
    {
        if (fgets(s[i], sizeof(s[i]), stdin) == 0)
            break;
// Remove newline from input
        size_t len = strlen(s[i]);
        assert(len > 0);
        s[i][len-1] = '\0';
    }
    n = i; // In case the file was shorter than stated!

    printf("Before:\n");
    for (i = 0; i < n; i++)
        printf("%s\n", s[i]);

    sort(s, n);

    printf("After:\n");
    for (i = 0; i < n; i++)
        printf("%s\n", s[i]);

    return 0;
}

void sort(char s[50][10], int n)
{
    int i, j, cmp;
    char tmp[10];

    if (n <= 1)
        return; // Already sorted

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n-1; j++)
        {
            cmp = strcmp(s[j], s[j+1]);

            if (cmp > 0)
            {
                strcpy(tmp, s[j+1]);
                strcpy(s[j+1], s[j]);
                strcpy(s[j], tmp);
            }
        }
    }
}
