#include "./inc/main.h"

void compare(void);

int main()
{
    system("clear");
    welcome();

    matrix_t matrix_a, matrix_b, matrix_res;
    sparse_t sparse_a, sparse_b, sparse_res;
    int dots_a, dots_b, dots_sum = 0;
    int percent_a, percent_b;

    int choice = -1;

    while (choice != 0)
    {
        if (input_interval(&choice, 0, 7))
        {
            printf("Incorect Input! try again\n");
            welcome();
        }

        else
        {
            if (choice == 1)
            {
                printf("Enter the Dimensions of Matrices [1 to 1000]: ");
                if (input_interval(&matrix_a.rows, 1, 1000) || input_interval(&matrix_a.columns, 1, 1000))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                printf("Enter The number of non-zero elements А [1 to %d]:  ", matrix_a.rows * matrix_a.columns);
                if (input_interval(&dots_a, 0, matrix_a.rows * matrix_a.columns))
                {
                    puts("Incorect Input! try again");
                    welcome();
                }

                puts("Enter the elements of matrix A in {row, col, val} format: ");
                create(&matrix_a);
                if (input(&matrix_a, dots_a))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                matrix_b.rows = matrix_a.rows;
                matrix_b.columns = matrix_a.columns;

                printf("Enter The number of non-zero elements B [1 to %d]:\n", matrix_a.rows * matrix_a.columns);
                if (input_interval(&dots_b, 0, matrix_b.rows * matrix_b.columns))
                {
                    puts("Incorect Input! try again");
                    welcome();
                }

                puts("Enter the elements of matrix B in {row, col, val} format: ");
                create(&matrix_b);
                if (input(&matrix_b, dots_b))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                matrix_res.rows = matrix_a.rows;
                matrix_res.columns = matrix_a.columns;

                create(&matrix_res);

                screate(&sparse_a, dots_a, matrix_a.columns);
                sinput(&sparse_a, matrix_a);
                fill_col_entry(&sparse_a, matrix_a);

                screate(&sparse_b, dots_b, matrix_a.columns);
                sinput(&sparse_b, matrix_b);
                fill_col_entry(&sparse_b, matrix_b);

                sdots(&sparse_a, &sparse_b, &dots_sum);
                screate(&sparse_res, dots_sum, matrix_a.columns);

                welcome();
            }

            if (choice == 2)
            {
                printf("Enter the Dimensions of Matrices [1 to 1000]: ");
                if (input_interval(&matrix_a.rows, 1, 1000) || input_interval(&matrix_a.columns, 1, 1000))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                printf("Enter the percentage of non-zero elements of matrix А [0 to 100]: ");
                if (input_interval(&percent_a, 0, 100))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                printf("Enter the percentage of non-zero elements of matrix B [0 to 100]: ");
                if (input_interval(&percent_b, 0, 100))
                {
                    puts("Incorect Input! try again");
                    return ok;
                }

                matrix_b.rows = matrix_a.rows;
                matrix_b.columns = matrix_a.columns;

                create(&matrix_a);
                create(&matrix_b);
                int to_fill_a = floor(matrix_a.rows * matrix_a.columns * percent_a / 100.0);
                int a_create = to_fill_a;
                while (to_fill_a)
                {
                    gorandom(&matrix_a, percent_a);
                    to_fill_a--;
                }
                int to_fill_b = floor(matrix_a.rows * matrix_a.columns * percent_b / 100.0);
                int b_create = to_fill_b;
                while (to_fill_b)
                {
                    gorandom(&matrix_b, percent_b);
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

                welcome();
            }

            if (choice == 3)
            {
                uint64_t ticks = 0;
                classic_sum(&matrix_a, &matrix_b, &matrix_res, &ticks);

                welcome();
            }

            if (choice == 4)
            {
                uint64_t ticks = 0;
                classic_sum(&matrix_a, &matrix_b, &matrix_res, &ticks);
                ticks = 0;
                fill_col_entry(&sparse_a, matrix_a);
                fill_col_entry(&sparse_b, matrix_b);
                sparse_sum(&sparse_a, &sparse_b, &sparse_res, &ticks);
                fill_col_entry(&sparse_res, matrix_res);

                welcome();
            }

            if (choice == 5)
            {
                puts("Matrix A: ");
                output(&matrix_a);

                puts("Matrix B: ");
                output(&matrix_b);

                puts("Res: ");
                output(&matrix_res);

                welcome();
            }

            if (choice == 6)
            {
                puts("Matrix A: ");
                soutput(sparse_a);

                puts("Matrix B: ");
                soutput(sparse_b);

                puts("Res: ");
                soutput(sparse_res);

                welcome();
            }
            if (choice == 7)
            {
                compare();
                welcome();
            }
            
        }
    }

    deletee(&matrix_a);
    sdelete(&sparse_a);
    deletee(&matrix_b);
    sdelete(&sparse_b);
    deletee(&matrix_res);
    sdelete(&sparse_res);

    return ok;
}