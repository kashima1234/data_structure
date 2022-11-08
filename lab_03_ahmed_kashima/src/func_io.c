#include <stdio.h>
#include <string.h>

#include "../inc/data_structures.h"
#include "../inc/defines.h"


// Welcomming print with available features.
void welcome()
{
    printf("%s",
           "\t|-------------------------------------------------------------| \n "\
           "\t|***** SPARSE MATRIX USING STANDARD AND COLUMNAR METHOD ******| \n "\
           "\t|**************************--+---*****************************| \n "\
           "\t| This program allows you to compare the time taken to add    | \n "\
           "\t| two sparse matrices stored as standard and sparse           | \n "\
           "\t| columnar views.                                             | \n "\
           "\t|**************************--+---*****************************| \n ");
    printf("%s",
           "\t| Select an action from the list by entering the appropriate  | \n"\
           "\t| number                                                      |\n"
           "\t|**************************--+---*****************************| \n ");
    printf("%s",
           "\t|[1]=> User input Matrix.                                     |\n"
           "\t|[2]=> Random Matrix by percent of non-zero elements.         |\n"
           "\t|[3]=> Addition of two matrix using standard storage method.  |\n"
           "\t|[4]=> Addition matrices using sparse columnar storage.       |\n"
           "\t|[5]=> Output source and result matrix using standard form.   |\n"
           "\t|[6]=> Output source and result matrix using columnar form.   |\n"
           "\t|[7]=> Time and Meomory complexity of Algorithm.              |\n"
           "\t|[0]=> EXIT.                                                  |\n"
           "\t|_____________________________________________________________|\n\n"
           "Your choice: ");
}

// Clean input stream from trash.
void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Input number in between.
int input_interval(type_t *const num, const type_t left, const type_t right)
{
    if (scanf(type_spec, num) != GOT_ARG)
    {
        clean_input_stream();
        return error;
    }

    if (*num < left || *num > right)
    {
        clean_input_stream();
        return error;
    }

    return ok;
}