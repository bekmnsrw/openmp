#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Написать программу, в которой объявить и присвоить начальные значения целочисленным массивам a[10] и b[10],
 * определить параллельную область, количество нитей задать равным 2,
 * выделить код для основной (номер 0) и нити с номером 1.
 * Основная нить (master) должна выполнять поиск min значения элементов массива a,
 * нить с номером 1 - поиск max значения элементов массива b.
 * Результат выдать на экран. (2 балла)
*/

int main()
{
    int a[10];
    int b[10];

    for (int i = 0; i < 10; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    int min = a[0];
    int max = b[0];

#pragma omp parallel firstprivate(a, b) shared(max, min) num_threads(2) default(none)
    {
        #pragma omp master
        {
            printf("Master Thread: %d\n", omp_get_thread_num());

            for (int i: a)
            {
                if (i < min)
                {
                    min = i;
                }
            }
        }

        #pragma omp single
        {
            printf("Single Thread: %d\n", omp_get_thread_num());

            for (int j : b)
            {
                if (j > max)
                {
                    max = j;
                }
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        printf("a%d = %d, b%d = %d\n", i, a[i], i, b[i]);
    }

    printf("------------------\n");

    printf("MIN: %d, MAX: %d\n", min, max);

    return 0;
}
