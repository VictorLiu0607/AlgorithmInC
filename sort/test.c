#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sort.h"

#define ARRAY_SIZE 1<<24
int main (int argc, char *argv[])
{
    int i;
    int *A;
    int *B;
    A = malloc(sizeof(int) * ARRAY_SIZE);
    B = malloc(sizeof(int) * ARRAY_SIZE);
    printf("start init.....\n");
    size_t size;
    clock_t start,end;
    time_t t;
    for (size = ARRAY_SIZE>>8; size <= ARRAY_SIZE; size = size << 2)
    {
        time(&t);
        srand(t);
        for (i = 0; i < size; i ++)
        {
            A[i] = B[i] = rand();
        }

        printf("Array[%zu] is unsorted!\n", size);

        printf("Sort with shell sort (sedgewick increasement)\n");
        start = clock();
        shell_sort_sedgewick(A, size);
        end = clock();
        printf("\tArray is %s\n", is_sorted(A, size)?"sorted":"unsorted");
        printf("\tSort over! time: %ld.%ldms\n", (long)(end - start)/1000, (long)(end - start) % 1000);

        printf("Sort with shell sort (hibbard increasement)\n");
        memcpy(A, B, size);
        start = clock();
        shell_sort_hibbard(A, size);
        end = clock();
        printf("\tArray is %s\n", is_sorted(A, size)?"sorted":"unsorted");
        printf("\tSort over! time: %ld.%ldms\n", (long)(end - start)/1000, (long)(end - start) % 1000);

        printf("Sort with QuickSort\n");
        memcpy(A, B, size);
        start = clock();
        QuickSort(A, size);
        end = clock();
        printf("\tArray is %s\n", is_sorted(A, size)?"sorted":"unsorted");
        printf("\tSort over! time: %ld.%ldms\n", (long)(end - start)/1000, (long)(end - start) % 1000);

        printf("Sort with heap sort\n");
        memcpy(A, B, size);
        start = clock();
        heap_sort(A, size);
        end = clock();
        printf("\tArray is %s\n", is_sorted(A, size)?"sorted":"unsorted");
        printf("\tSort over! time: %ld.%ldms\n", (long)(end - start)/1000, (long)(end - start) % 1000);

        printf("Sort with merge sort\n");
        memcpy(A, B, size);
        start = clock();
        merge_sort(A, size);
        end = clock();
        printf("\tArray is %s\n", is_sorted(A, size)?"sorted":"unsorted");
        printf("\tSort over! time: %ld.%ldms\n", (long)(end - start)/1000, (long)(end - start) % 1000);

        printf("\n\n");
    }

    return 0;
}
