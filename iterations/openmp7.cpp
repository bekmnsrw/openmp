#include <cstdio>
#include <cstdlib>
#include <omp.h>

/*
 * Написать программу, в которой определить две параллельные области, каждая из которых содержит итерационную
 * конструкцию for выполняющую инициализацию элементов одномерных массивов целых чисел a[12], b[12] и c[12].
 * Число нитей перед первой областью задать равным 3, перед второй – равным 4.
 * Первая параллельная область выполняет инициализацию элементов массивов a и b
 * с использованием статического распределения итераций, размер порции итераций выбрать самостоятельно,
 * вторая параллельная область выполняет инициализацию элементов массива c по следующему правилу c[i] = a[i] + b[i],
 * с использованием динамического распределения итераций, размер порции итераций выбрать самостоятельно.
 * В каждой области определить и выдать на экран количество нитей, номер нити и результат выполнения цикла.
 * Убедиться в правильности работы программы.  (2 баллов)
*/

int main()
{
    int a[12];
    int b[12];
    int c[12];

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for schedule(static, 4)
        for (int i = 0; i < 12; i++)
        {
            printf("Iter: %d, Thread: %d, Threads Num: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
            a[i] = rand() % 100;
            b[i] = rand() % 100;
        }
    }

    printf("-----------------------------------\n");

    /* Вывод значений массива а */
    printf("a: ");

    for (int i = 0; i < 12; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    /* Вывод значений массива b */
    printf("b: ");

    for (int i = 0; i < 12; i++)
    {
        printf("%d ", b[i]);
    }

    printf("\n");

    printf("-----------------------------------\n");

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for schedule(dynamic, 3)
        for (int i = 0; i < 12; i++)
        {
            printf("Iter: %d, Thread: %d, Threads Num: %d\n", i, omp_get_thread_num(), omp_get_num_threads());
            c[i] = a[i] + b [i];
        }
    }

    printf("-----------------------------------\n");

    printf("c: ");

    for (int i = 0; i < 12; i++)
    {
        printf("%d ", c[i]);
    }

    return 0;
}