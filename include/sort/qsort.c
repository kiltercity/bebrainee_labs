#include <stdio.h>

void qsort(int v[], int left, int right);


int main (void)

{
    int array[10] = { 3,45,2,5,19,50,4, 7, 9, 1};

    qsort(array, 0, 10);

    int c = 10;


    while (--c)
    {
        printf("%d ", array[10 - c]);
    }

    return 0;
}


void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right)
        return;

    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
    {
        if (v[i] < v[left])
            swap(v, ++last, i);
    }
    printf("setup: last: %d\n", last);
        
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}

void swap (int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}