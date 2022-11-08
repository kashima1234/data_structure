#include <stdio.h>
#include <stdlib.h>

#include "../inc/defines.h"
#include "../inc/data_structures.h"

#include "../inc/func_io.h"

void fill_matrix(matrix_t *const matrix)
{
    for (int row = 0; row < matrix->rows; ++row)
    {
        for (int col = 0; col < matrix->columns; ++col)
        {
            *(*(matrix->matrix + row) + col) = 0;
        }
    }
}

int create(matrix_t *const matrix)
{
    matrix->matrix = (type_t **)malloc(matrix->rows * sizeof(type_t *));

    if (!matrix->matrix)
        return error;

    for (int row = 0; row < matrix->rows; ++row)
    {
        *(matrix->matrix + row) = (type_t *)malloc(matrix->columns * sizeof(type_t));

        if (!*(matrix->matrix + row))
        {
            for (int clean = 0; clean < row; ++clean)
            {
                free(*(matrix->matrix + clean));
            }

            free(matrix->matrix);

            return error;
        }
    }

    fill_matrix(matrix);

    return ok;
}

int deletee(matrix_t *const matrix)
{
    if (matrix->matrix == NULL)
        return error;

    for (int clean = 0; clean < matrix->rows; ++clean)
    {
        if (*(matrix->matrix + clean))
        {
            free(*(matrix->matrix + clean));
        }
    }

    free(matrix->matrix);

    return ok;
}

int input(matrix_t *const matrix, const int dots)
{
    if (!matrix->matrix)
    {
        return error;
    }

    for (int dot = 0; dot < dots; ++dot)
    {
        int row, col, cur;

        if (input_interval(&row, 0, matrix->rows - 1))
            return error;

        if (input_interval(&col, 0, matrix->columns - 1))
            return error;

        if (input_interval(&cur, -1000, 99999))
            return error;

        *(*(matrix->matrix + row) + col) = cur;
    }

    return ok;
}

int output(const matrix_t *const matrix)
{
    if (matrix->matrix == NULL)
        return error;

    for (int row = 0; row < matrix->rows; ++row)
    {
        for (int col = 0; col < matrix->columns; ++col)
            printf(out_spec, *(*(matrix->matrix + row) + col));
        printf("\n");
    }

    return ok;
}
