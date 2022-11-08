#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

enum error_code
{
    ok,
    error
};

typedef struct node
{
    char data;
    struct node *next;
} node_t;

typedef struct add_node
{
    void *p;
    struct add_node *next;
} node_add_t;

typedef struct
{
    node_t *head;
} stack_t;

typedef struct
{
    char *data;
    int used_elems;
} arr_stack_t;

#endif //_DATA_STRUCT_H_