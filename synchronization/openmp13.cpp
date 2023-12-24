#include <cstdio>
#include <omp.h>

/*
 * Модифицируйте задачу 1 так, чтобы потоки распечатывали свои идентификаторы в обратном (убывающем) порядке.
 * Существует как минимум 5 способов решения. Постарайтесь найти как можно больше.
 * (каждый вариант 1 балл – max 5 баллов)
 *
 * Написать программ, где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World».
 * Запустить программу с 8 потоками.
*/

int main()
{
    #pragma omp parallel num_threads(8)
    {
        for (int i = 7; i >= 0; i--)
        {
            #pragma omp barrier
            {
                if (i == omp_get_thread_num())
                {
                    #pragma omp critical
                    printf("Thread ID: %d\n", omp_get_thread_num());
                }
            }
        }
    }

    printf("------------\n");

    /* 2 - lock */
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel num_threads(8)
    {
        for (int i = 7; i >= 0; i--)
        {
            #pragma omp barrier
            if (i == omp_get_thread_num())
            {
                omp_set_lock(&lock);
                printf("Thread ID: %d\n", omp_get_thread_num());
                omp_unset_lock(&lock);
            }
        }
    }

    omp_destroy_lock(&lock);

    printf("------------\n");
}

