#include <cstdio>
#include <cstdlib>

/*
 * Написать программу, в которой объявить и присвоить начальные значения целочисленному массиву a[100].
 * Используя конструкцию parallel for и reduction вычислить средние арифметические значения элементов массива a.
 * Одно при помощи reduction, другое без. Сравнить полученные значения. Объяснить возможную разность результатов. (2 балла)
*/

int main()
{
    int a[100];

    for (int i = 0; i < 100; i++)
    {
        a[i] = rand() % 100;
    }

    int sum_with_reduction = 0;
    int sum_without_reduction = 0;

    #pragma omp parallel for reduction(+:sum_with_reduction)
    for (int i = 0; i < 100; i++)
    {
        sum_with_reduction += a[i];
    }

    #pragma omp parallel for
    for (int i = 0; i < 100; i++)
    {
        sum_without_reduction += a[i];
    }

    printf("AVG with reduction: %d\n", sum_with_reduction / 100);
    printf("AVG without reduction: %d\n", sum_without_reduction / 100);

    return 0;

/*
 * Если используем reduction(), то для каждой переменной создаются локальные копии в каждом потоке.
 * Над локальными копиями переменных после выполнения всех операторов параллельной области выполняется заданный оператор.
 * Поэтому, если мы не используем reduction(), то может возникнуть такая ситуация, что нить обращается к переменной,
 * значение которой не актуально (ее значение уже было изменено).
*/
}
