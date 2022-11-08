#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char c[] = "Ahmad Khalid Karimzai";
    char *copy = malloc(strlen(c) + 1);
    strcpy(copy, c);
    puts(copy);
    free(copy);
    return 0;
}