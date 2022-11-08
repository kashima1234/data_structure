#include "../inc/arr_stack.h"

int is_empty_arr_stk(arr_stack_t *stk)
{
    return stk->used_elems == -1;
}

void init_arr_stack(arr_stack_t **stk)
{
    *stk = malloc(sizeof(arr_stack_t));
    if (*stk)
    {
        (*stk)->data = calloc(6, sizeof(char));
        (*stk)->used_elems = -1;
    }
}

void init_arr_stack_for_testing(arr_stack_t **stk, size_t size)
{
    *stk = malloc(sizeof(arr_stack_t));
    if (*stk)
    {
        (*stk)->data = calloc(size, sizeof(char));
        (*stk)->used_elems = -1;
    }
}

void push_arr_for_testing(arr_stack_t *stk, char data, size_t size)
{
    stk->data[++stk->used_elems] = data;
}

void push_arr(arr_stack_t *stk, char data)
{
    if (stk->used_elems == 5)
    {
        puts("stack overflow");
        return;
    }
    // printf("%c ", data);
    // printf("%d", stk->used_elems);
    stk->data[++stk->used_elems] = data;
}

char pop_arr(arr_stack_t *stk)
{
    if (is_empty_arr_stk(stk))
        return -1;
    // puts("first timr");
    return stk->data[stk->used_elems--];
}

void free_arr_stk(arr_stack_t *stk)
{
    if (stk)
    {
        if (stk->data)
            free(stk->data);
        free(stk);
    }
}

void print_arr_stack(arr_stack_t *stk)
{
    if (is_empty_arr_stk(stk))
    {
        puts("\nEmpty stack!\n");
        return;
    }
    int i = stk->used_elems;
    printf("\npushed to stack elements are:\n\t\t[");
    for (; i >= 0; i--)
        printf("%c ,", stk->data[i]);
    printf("]\n\n");
}

void print_arr_stack_like_arr(arr_stack_t *stk)
{
    if (is_empty_arr_stk(stk))
    {
        puts("\nEmpty stack!\n");
        return;
    }
    int i = stk->used_elems;
    printf("\nIndex: ");
    for (int j = 0; j <= i; j++)
        printf("|%d", j);
    printf("|\n");
    printf("Array: ");
    for (int j = 0; j <= i; j++)
        printf("|%c", stk->data[j]);
    printf("|\n\n");
}
