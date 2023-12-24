#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Используя возможности OpenMP написать программу умножения матрицы на вектор.
 * Сравнить время выполнения последовательной и параллельных программ (выбрать наилучший schedule).
 * Определить размеры матрицы при которых параллельная программа начинает работать быстрей последовательной (3 балла)
*/

int main()
{
    int matrix_row = 700;
    int matrix_column = 700;
    int matrix[matrix_row][matrix_column];

    int vector_row = matrix_column;
    int vector[vector_row];

    int result[matrix_row];

    /* Заполнение матрицы */
    for (int i = 0; i < matrix_row; i++)
    {
        for (int j = 0; j < matrix_column; j++)
        {
            matrix[i][j] = rand();
        }
    }

    /* Заполнение вектора */
    for (int i = 0; i < vector_row; i++)
    {
        vector[i] = rand();
    }

    /* Вывод матрицы */
/*    for (int i = 0; i < matrix_row; i++)
 *    {
 *        for (int j = 0; j < matrix_column; j++)
 *        {
 *            printf("%d ", matrix[i][j]);
 *        }
 *        printf("\n");
 *    }
 *
 *   printf("-----------------\n");
*/

    /* Вывод вектора */
/*    for (int i = 0; i < vector_row; i++)
 *    {
 *        printf("%d\n", vector[i]);
 *    }
 *
 *    printf("-----------------\n");
*/

    /* Умножение матрицы на вектор без распараллеливания */
    double t1 = omp_get_wtime();
    for (int i = 0; i < matrix_row; i++)
    {
        result[i] = 0;

        for (int j = 0; j < matrix_column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    printf("Time without parallel: %f\n", omp_get_wtime() - t1);

    /* Вывод результата умножения */
/*    for (int i = 0; i < matrix_row; i++)
 *    {
 *        printf("%d\n", result[i]);
 *    }
 *
 *    printf("-----------------\n");
*/

    /* Умножение матрицы на вектор с распараллеливанием */
    double t2 = omp_get_wtime();
    printf("%f\n", t2);
    #pragma omp parallel for schedule(static) firstprivate(result)
    for (int i = 0; i < matrix_row; i++)
    {
        result[i] = 0;

        for (int j = 0; j < matrix_column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    printf("%f\n", omp_get_wtime());
    printf("Time with parallel (static schedule): %f\n", omp_get_wtime() - t2);

    double t3 = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) firstprivate(result)
    for (int i = 0; i < matrix_row; i++)
    {
        result[i] = 0;

        for (int j = 0; j < matrix_column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    printf("Time with parallel (dynamic schedule): %f\n", omp_get_wtime() - t3);

    double t4 = omp_get_wtime();
    #pragma omp parallel for schedule(guided) firstprivate(result)
    for (int i = 0; i < matrix_row; i++)
    {
        result[i] = 0;

        for (int j = 0; j < matrix_column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    printf("Time with parallel (dynamic schedule): %f\n", omp_get_wtime() - t4);

    double t5 = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) firstprivate(result)
    for (int i = 0; i < matrix_row; i++)
    {
        result[i] = 0;

        for (int j = 0; j < matrix_column; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    printf("Time with parallel (runtime schedule): %f\n", omp_get_wtime() - t5);
}
