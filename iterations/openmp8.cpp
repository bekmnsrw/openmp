#include <cstdio>
#include <omp.h>
#include <ctime>

/*
 * Написать программу, в которой объявлен массив из 16000 элементов и инициализирован так,
 * что значение элемента массива равно его порядковому номеру.
 * Затем создайте результирующий массив, в котором (за исключением крайних элементов) будут средние значения исходного массива:
 * b[i] = (a[i-1] + a[i] + a[i+1])/3.0
 * Запустите программу с 8-ю процессами при различных типах распределения работ
 * (static, dynamic, guided, auto(runtime, если auto не работает)) и посмотреть время на разных размерах порций. (4 балла)
*/

int main()
{
    int a[16000];
    float b[16000];

    for (int i = 0; i < 16000; i++)
    {
        a[i] = i;
    }

    clock_t start1 = clock();
    double t1 = omp_get_wtime();
    printf("%f\n", t1);
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(static, 32)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    clock_t finish1 = clock();
    printf("%f\n", omp_get_wtime());
    printf("Static (2 chunks): %f\n", (double)(finish1 - start1)/1000.0);

    double t2 = omp_get_wtime();
    clock_t start2 = clock();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(static, 160)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    clock_t finish2 = clock();
    printf("Static (160 chunks): %f\n", (double)(finish2 - start2)/1000.0);

    double t3 = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(dynamic, 32)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    printf("Dynamic (2 chunks): %f\n", omp_get_wtime() - t3);

    double t4 = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(dynamic, 160)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    printf("Dynamic (160 chunks): %f\n", omp_get_wtime() - t4);

    double t5 = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(guided, 32)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    printf("Guided (2 chunks): %f\n", omp_get_wtime() - t5);

    double t6 = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(guided, 160)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    printf("Guided (160 chunks): %f\n", omp_get_wtime() - t6);

    double t7 = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(runtime)
        for (int i = 1; i < 16000 - 1; i++)
        {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
        }
    }
    printf("Runtime: %f\n", omp_get_wtime() - t7);

    return 0;
}
