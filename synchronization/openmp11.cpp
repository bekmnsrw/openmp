#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Написать программу, в которой объявить и присвоить начальные значения массиву целых чисел a[30],
 * для инициализации значений использовать генератор случайных чисел.
 * Используя конструкцию omp parallel for и omp atomic вычислить количество элементов массива,
 * числовые значения которых кратны 9.
 * Количество нитей задать самостоятельно. Результат выдать на экран. (2 балла)
*/

int main()
{
    int a[30];
    int counter = 0;

    for (int i = 0; i < 30; i++)
    {
        a[i] = rand() % 100;
    }

    for (int i = 0; i < 30; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    #pragma omp parallel for shared(counter)
    for (int i = 0; i < 30; i++)
    {
        if (a[i] % 9 == 0)
        {
            #pragma omp atomic
            counter++;
        }
    }

    printf("COUNTER: %d\n", counter);
}
