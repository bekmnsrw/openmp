#include <cstdio>
#include <omp.h>

/*
 * Написать программу где каждый поток печатает:
 *     1) свой идентификатор
 *     2) количество потоков всего
 *     3) строчку «Hello World»
 * Запустить программу с 8 потоками.
 * Всегда ли вывод идентичен? Почему?
*/

int main()
{
#pragma omp parallel num_threads(8) default(none)
    {
        printf(
                "Thread ID: %d, Total Threads' Number: %d, Hello, World!\n",
                omp_get_thread_num(),
                omp_get_num_threads()
        );
    }

    return 0;
}

/*
 * Нет соглашения о том, что нити выполняются последовательно,
 * от нулевой нити до последней. Более того, при выводе данных
 * они получают доступ к консоли в неопределенном порядке ("асинхронное выполнение кода")
*/
