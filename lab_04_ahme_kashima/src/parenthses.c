#include "../inc/parenthses.h"

int baracket(char x)
{
    if (x == '{' || x == '[' || x == '(')
        return OPENED;
    else if (x == '}' || x == ']' || x == ')')
        return CLOSED;
    return 0;
}

int check_balanced(char lhs, char rhs)
{
    if (lhs == '{' && rhs == '}')
        return ok;
    else if (lhs == '[' && rhs == ']')
        return ok;
    else if (lhs == '(' && rhs == ')')
        return ok;
    return error;
}

void check_string_using_ll(char *string)
{
    stack_t *stk = NULL;
    init_stack_node(&stk);
    int flag = ok, pushed = error;
    char x;
    if (string == NULL || stk == NULL)
    {
        puts("stacxk overflow");
        return;
    }
    for (size_t i = 0 ; i < strlen(string); i++)
    {
        char c = string[i];
        if (baracket(c) == OPENED)
        {
            push(stk, create_node(c));
            pushed = ok;
        }
        else if (baracket(c) == CLOSED)
        {
            if (check_balanced(pop(stk,NULL), c) == error)
            {
                flag = error;
                break;
            }
        }
    }
    if (pushed == ok)
    {
        if (flag == ok && is_empty(stk))
            puts("Balanced.");
        else
            puts("Not Balanced.");
    }
    else
        puts("inputed string without any bracket!");
    free(string);
    free_linked_list_stk(stk);
}

void check_string_using_arr(char *string)
{
    arr_stack_t *stk = NULL;
    init_arr_stack(&stk);
    int flag = ok, pushed = error;
    char x;
    if (string == NULL || stk == NULL)
    {
        puts("memory leac or incorrect input!");
        return;
    }
    for (size_t i = 0 ; i < strlen(string); i++)
    {
        if (baracket(string[i]) == OPENED)
        {
            push_arr(stk, string[i]);
            pushed = ok;
        }
        else if (baracket(string[i]) == CLOSED)
        {
            pushed = ok;
            if (check_balanced(pop_arr(stk), string[i]) == error)
            {
                flag = error;
                break;
            }
        }
    }
    if (pushed == ok)
    {
        if (flag == ok && is_empty_arr_stk(stk))
            puts("\nBalanced.");
        else
            puts("\nNot balanced.");
        // free(string);
    }
    else
        puts("\ninputed string without any bracket!\n");
    free_arr_stk(stk);
    // puts("finshed");
}
