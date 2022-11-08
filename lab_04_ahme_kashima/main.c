#include "./inc/main.h"

void welcome(void)
{
    printf("\t*******************************++++++++++*******************************\n"\
           "\t*    Parethesis of Equation using stack                                *\n"\
           "\t*   [1]-> check parentheses of Brackets                                *\n"\
           "\t*   [2]-> Time and Memory Complexity of Array and Linked List stack    *\n"\
           "\t*                 *****Linked List Stak****                            *\n"\
           "\t*   [3]-> push                                                         *\n"\
           "\t*   [4]-> pop                                                          *\n"\
           "\t*   [5]-> print stack                                                  *\n"\
           "\t*   [6]-> print stack like linked-list                                 *\n"\
           "\t*   [7]-> print freed adresses.                                        *\n"\
           "\t*                    ****Array Stack****                               *\n"\
           "\t*   [8]-> push                                                         *\n"\
           "\t*   [9]-> pop                                                          *\n"\
           "\t*   [10]-> print stack                                                  *\n"\
           "\t*   [11]-> print stack like array                                      *\n"\
           "\t*   [0]-> Exit                                                         *\n"\
           "\t*******************************++++++++++*******************************\n");
}

void clear_stream()
{
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF) {}
}

int main()
{
    int choice;
    stack_t *stk = NULL;
    node_add_t *addresses = NULL, *temp = NULL;
    init_stack_node(&stk);
    arr_stack_t *arr_stk = NULL;
    init_arr_stack(&arr_stk);
    char *string = NULL;
    char x;
    size_t len;
    ssize_t read;
    uint64_t start, end;

    system("clear");
    if (stk && arr_stk)
    {
        do
        {
            welcome();
            printf("Your Choice: ");
            if (fscanf(stdin, "%d", &choice) != 1)
            {
                puts("Incorect Input! try again");
                break;
            }
            switch (choice)
            {
            case 0:
                return 0;
            case 1:
                clear_stream();
                puts("input Equation:\n");
                read = getline(&string, &len, stdin);
                string[read - 1] = '\0';
                check_string_using_arr(string);
                break;
            case 2:
                compare();
                break;
            case 3:
                clear_stream();
                puts("Input a single symbol in ASCII: ");
                if (fscanf(stdin, "%c", &x))
                {
                    push(stk, create_node(x));
                    puts("\npushed\n");
                }
                else
                    puts("Incorect input!");
                break;
            case 4:
                x = pop(stk, &addresses);
                if (x == -1)
                    puts("\nEmpty Stack!\n");
                else
                {
                    printf("\nsuccessfully removed.\nremoved element");
                    printf("\t{%c}\n", x);
                }
                break;
            case 5:
                print_stack(stk);
                break;
            case 6:
                print_stack_linked_list(stk);
                break;
            case 7:
                if (addresses == NULL)
                    puts("empty address list");
                else
                {
                    temp = addresses;
                    while (temp)
                    {
                        printf("\t[%p]\n", temp->p);
                        temp = temp->next;
                    }
                }
                break;
            case 8:
                clear_stream();
                puts("Input a single symbol in ASCII: ");
                if (fscanf(stdin, "%c", &x))
                {
                    start = tick();
                    push_arr(arr_stk, x);
                    end = tick();
                    puts("\npushed\n");
                    printf("Element pushed in %ju time unit:\n\n\n", end - start);
                }
                else
                    puts("Incorect input!");
                break;
            case 9:
                start = tick();
                x = pop_arr(arr_stk);
                end = tick();
                if (x == -1)
                    puts("\nEmpty Stack!\n");
                else
                {
                    printf("\nsuccessfully removed.\npushed element");
                    printf("\t{%c}\n", x);
                }
                break;
            case 10:
                print_arr_stack(arr_stk);
                break;
            case 11:
                print_arr_stack_like_arr(arr_stk);
                break;
            default:
                puts("Incorect Input! try again.");
                break;
            }
        } while (choice);
        free(string);
        free_arr_stk(arr_stk);
        free_linked_list_stk(stk);
        free_add_list(addresses);
    }
    return ok;
}