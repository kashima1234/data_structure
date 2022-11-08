#include "../inc/compare.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void calculate_eff(size_t size)
{
    uint64_t start, end, arr_test;
    stack_t *stk;
    arr_stack_t *arr_stk;
    init_arr_stack_for_testing(&arr_stk, size);
    init_stack_node(&stk);
    start = tick();
    for (size_t i = 0; i < size; i++)
        push_arr_for_testing(arr_stk, 1, size);
    for(int i = 0; i < size; i++)
        pop_arr(arr_stk);
    end = tick();
    arr_test = end - start;
    start = tick();
    for (size_t i = 0; i < size; i++)
        push(stk, create_node(1));

    for(int i = 0; i < size; i++)
        pop(stk, NULL);
    end = tick();
    size_t size_arr = size * sizeof(arr_stk->data[0]) + 2 * sizeof(arr_stk->used_elems);
    size_t size_list = (size * (sizeof(char) + sizeof(stk->head))) + sizeof(stk);
    printf("|%10lu |      %15ju      |   %21ju        |     %11lu     |    %19lu    |\n", size, arr_test, end - start, size_arr, size_list);
    // printf("          %4.2lf%%        |     %8ld       |    %8ld       |                     %ld%%|\n", 100 - arr_test * 100 / time_res2,
    //        size_arr, size_list, 100 - size_arr * 100 / size_list);
    free_arr_stk(arr_stk);
    free_linked_list_stk(stk);
}

void compare()
{
    puts("\t\t\t\t----TIME AND MEMORY COMPLEXITY OF ALGORITHM----");
    puts ("|stack size | Array: push and pop time  | Linked list: push and pop time | sizeof(array stack) | sizeof(linked list stack) |");
    puts("----------------------------------------------------------------------------------------------------------------------------");
    int check_size[] = {10, 50, 100, 250, 500, 1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 9; i++)
        calculate_eff(check_size[i]);
    puts("----------------------------------------------------------------------------------------------------------------------------");
}