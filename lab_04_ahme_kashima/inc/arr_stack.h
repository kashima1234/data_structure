#ifndef _ARR_STACK_H_
#define _ARR_STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include "data_struct.h"

char pop_arr(arr_stack_t *stk);

void push_arr(arr_stack_t *stk, char data);

void free_arr_stk(arr_stack_t *stk);

void init_arr_stack(arr_stack_t **stk);

void print_arr_stack(arr_stack_t *stk);

void print_arr_stack_like_arr(arr_stack_t *stk);

int is_empty_arr_stk(arr_stack_t *stk);

void push_arr_for_testing(arr_stack_t *stk, char data, size_t size);

void init_arr_stack_for_testing(arr_stack_t **stk, size_t size);

#endif //_ARR_STACK_H_