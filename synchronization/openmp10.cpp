#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Написать программу, в которой объявить и присвоить начальные значения элементам двумерного массива d[6][8],
 * для инициализации значений использовать генератор случайных чисел.
 * Используя конструкцию директивы omp parallel for и omp critical определить
 * минимальное и максимальное значения элементов двумерного массива.
 * Реализовать аналог reduction для max и min.
 * Количество нитей задать самостоятельно. Результат выдать на экран. (2 балла)
*/

int main()
{
    int d[6][8];
    int max = -1;
    int min = 101;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            d[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    #pragma omp parallel num_threads(6)
    for (int i = 0; i < 6; i++)
    {
        #pragma omp for
        for (int j = 0; j < 8; j++)
        {
            if (d[i][j] > max)
            {
                #pragma omp critical
                if (d[i][j] > max)
                {
                    max = d[i][j];
                }
            }

            if (d[i][j] < min)
            {
                #pragma omp critical
                if (d[i][j] < min)
                {
                    min = d[i][j];
                }
            }
        }
    }

    printf("MAX: %d\n", max);
    printf("MIN: %d\n", min);
}
