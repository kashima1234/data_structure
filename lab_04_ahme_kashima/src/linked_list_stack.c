#include "../inc/linked_list_stack.h"

void init_stack_node(stack_t **stk)
{
    *stk = malloc(sizeof(stack_t));
    if (*stk)
        (*stk)->head = NULL;
}

node_t *create_node(char x)
{
    node_t *temp = malloc(sizeof(node_t));
    if (temp)
    {
        temp->data = x;
        temp->next = NULL;
    }
    return temp;
}

int is_empty(stack_t *stk)
{
    return stk->head == NULL;
}

void push(stack_t *stk, node_t *node)
{
    node->next = stk->head;
    stk->head = node;
    // printf("Address of pushed node: %p\n", node);
    // printf("Address of pushed data: %p\n", node->data);

}

node_add_t *create_add_node(void *p)
{
    node_add_t *temp = malloc(sizeof(node_add_t));
    temp->p = p;
    temp->next = NULL;
}

void push_to_add(node_add_t **add, node_add_t *current)
{
    if ((*add) == NULL)
        (*add) = current;
    else
    {
        node_add_t *temp = (*add);
        while (temp->next)
            temp = temp->next;
        temp->next = current;
    }
}

char pop(stack_t *stk, node_add_t **add)
{
    if (is_empty(stk))
        return -1;
    char temp = stk->head->data;
    node_t *current = stk->head;
    stk->head = stk->head->next;
    // printf("Address of poped node: %p\n", current);
    // printf("Address of poped data: %p\n", current->data);
    if (add)
        push_to_add(add, create_add_node(current));
    // free(current);
    return temp;
}

void free_linked_list_stk(stack_t *stk)
{
    if (stk)
    {
        node_t *temp;
        while (stk->head)
        {
            temp = stk->head;
            stk->head = stk->head->next;
            free(temp);
        }
        free(stk);
    }
}

void print_stack(stack_t *stk)
{
    if (stk->head == NULL)
    {
        puts("\nEmpty stack!\n");
        return;
    }
    node_t *temp = stk->head;
    printf("\nstack elements are:\n");
    while (temp)
    {
        printf("[element: %c, ", temp->data);
        printf("Address of node: %p, Address of data : %p]\n", temp, temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

void print_stack_linked_list(stack_t *stk)
{
    if (stk->head == NULL)
    {
        puts("\nEmpty stack!\n");
        return;
    }
    node_t *temp = stk->head;
    printf("\nhead:[");
    while (temp)
    {
        printf("%c, next]->[", temp->data);
        temp = temp->next;
    }
    printf("NULL]\n\n");
}

void free_add_list(node_add_t *head)
{
    if (head)
    {
        node_add_t *temp = NULL;
        while (head)
        {
            temp = head;
            free(temp->p);
            free(temp);
            head = head->next;
        }
    }
}