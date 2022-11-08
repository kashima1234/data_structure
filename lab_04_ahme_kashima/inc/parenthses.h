#ifndef _PARENTHSES_H_
#define _PARENTHSES_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_struct.h"
#include "arr_stack.h"
#include "linked_list_stack.h"

#define OPENED 1
#define CLOSED -1

void check_string_using_ll(char *string);

void check_string_using_arr(char *string);

#endif //_PARENTHSES_H_