#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Написать программу, в которой, объявить и заполнить случайными значениями массив целых чисел.
 * Используя возможности OpenMP найти максимальное значение элементов массива кратных 7.
 * Длину массива и количество потоков определить самостоятельно. Результат выдать на экран.
 * Для синхронизации числовых значений максимума используется механизм omp_lock. (2 балла)
*/

int main()
{
    int a[30];
    int max = 0;

    for (int i = 0; i < 30; i++)
    {
        a[i] = rand() % 100;
    }

    for (int i = 0; i < 30; i++)
    {
        printf("%d ", a[i]);
    }

   printf("\n");

    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel for shared(max)
    for (int i = 0; i < 30; i++)
    {
        if (a[i] % 7 == 0 && a[i] > max)
        {
            omp_set_lock(&lock);
            if (a[i] % 7 == 0 && a[i] > max)
            {
                max = a[i];
            }
            omp_unset_lock(&lock);
        }
    }

    printf("MAX multiple of 7: %d\n", max);

    omp_destroy_lock(&lock);
}

