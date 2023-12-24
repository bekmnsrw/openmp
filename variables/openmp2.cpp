#include <cstdio>
#include <omp.h>

/*
 * Написать программу, в которой определить две параллельные области,
 * выполнение которых зависит от условного оператора #pragma omp parallel if(…),
 * если заданное значение числа нитей больше 2, область выполняется параллельно, иначе не параллельно.
 * Число нитей перед первой областью задать равным 3, перед второй – равным 2.
 * Внутри параллельных областей определить количество нитей и номер каждой нити, результат выдать на экран.
 * Убедиться в правильности работы программы. (2 балла)
*/

int main()
{
    omp_set_num_threads(3);

#pragma omp parallel if (omp_get_max_threads() > 2) default(none)
    {
        printf(
                "First Parallel Scope: Thread ID: %d, Total Number Of Threads: %d\n",
                omp_get_thread_num(),
                omp_get_num_threads()
        );
    }

    omp_set_num_threads(2);

#pragma omp parallel if (omp_get_max_threads() > 2) default(none)
    {
        printf(
                "Second Parallel Scope: Thread ID: %d, Total Number Of Threads: %d\n",
                omp_get_thread_num(),
                omp_get_num_threads()
        );
    }

    return 0;
}
