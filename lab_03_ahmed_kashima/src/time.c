#include "../inc/main.h"

#define ITER 10

void time_testing(size_t dimen, size_t ele_perc)
{
    matrix_t matrix_a, matrix_b, matrix_res;
    sparse_t sparse_a, sparse_b, sparse_res;
    int dots_sum = 0;
    uint64_t start, end;


    puts("------------------------------------------------------------------------------------");

    printf("|%10lu |%5lu |", dimen, ele_perc);

    matrix_a.rows = matrix_a.columns = dimen;

    matrix_b.rows = matrix_a.rows;
    matrix_b.columns = matrix_a.columns;

    create(&matrix_a);
    create(&matrix_b);
    int to_fill_a = floor(matrix_a.rows * matrix_a.columns * ele_perc / 100.0);
    int a_create = to_fill_a;
    while (to_fill_a)
    {
        gorandom(&matrix_a, ele_perc);
        to_fill_a--;
    }
    int to_fill_b = floor(matrix_a.rows * matrix_a.columns * ele_perc / 100.0);
    int b_create = to_fill_b;
    while (to_fill_b)
    {
        gorandom(&matrix_b, ele_perc);
        to_fill_b--;
    }

    matrix_res.rows = matrix_a.rows;
    matrix_res.columns = matrix_a.columns;

    create(&matrix_res);

    screate(&sparse_a, a_create, matrix_a.columns);
    sinput(&sparse_a, matrix_a);
    fill_col_entry(&sparse_a, matrix_a);

    screate(&sparse_b, b_create, matrix_a.columns);
    sinput(&sparse_b, matrix_b);
    fill_col_entry(&sparse_b, matrix_b);

    sdots(&sparse_a, &sparse_b, &dots_sum);
    screate(&sparse_res, dots_sum, matrix_a.columns);

    uint64_t ticks = tick();
    start = tick();
    for (size_t i = 0; i < 10; i++)
        classic_sum(&matrix_a, &matrix_b, &matrix_res, &ticks);
    end = tick();
    printf("%15ju  %12luB |", (end - start) / 10, sizeof(type_t **) + 
                               sizeof(type_t *) * matrix_res.rows + 
                               sizeof(type_t) * matrix_res.rows * matrix_res.columns + 
                               2 * sizeof(int));
    ticks = 0;
    fill_col_entry(&sparse_a, matrix_a);
    fill_col_entry(&sparse_b, matrix_b);
    sparse_sum(&sparse_a, &sparse_b, &sparse_res, &ticks);
    fill_col_entry(&sparse_res, matrix_res);

    ticks = 0;
    sparse_sum(&sparse_a, &sparse_b, &sparse_res, &ticks);
    fill_col_entry(&sparse_res, matrix_res);


    printf("%15ju  %12luB |\n", ticks, sizeof(type_t *) * 3 +
                                  sizeof(type_t) * sparse_res.elems_amount * 2 + 
                                  sizeof(type_t) * sparse_res.cols_amount +
                                  2 * sizeof(int));
    deletee(&matrix_a);
    sdelete(&sparse_a);
    deletee(&matrix_b);
    sdelete(&sparse_b);
    deletee(&matrix_res);
    sdelete(&sparse_res);
}

void compare(void)
{
    puts("| Dimension |per(%)| Standard: time           size |Sparse:  time            size  |");
    int non_zero[] = {5, 10, 20, 30, 40, 50};
    int size_of_arr[] = {10, 50, 100, 200, 400};
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            time_testing(size_of_arr[i], non_zero[j]);
    puts("------------------------------------------------------------------------------------");
}