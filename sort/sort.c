#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int A[], int N)
{
    int j, p;
    int temp;
    for (p = 1; p < N; p++)
    {
        temp = A[p];
        for (j = p; j > 0 && A[j-1] > temp; j--)
            A[j] = A[j - 1];
        A[j] = temp;
    }
}

static int sedgewick_queue[28] = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929, 37730305, 67084289, 150958081, 268386305, 603906049, 1073643521};

void shell_sort(int A[], int N)
{
    int i, j, increment;
    int temp;

    for (increment = N / 2; increment > 0; increment /= 2)
    {
        for (i = increment; i<N; i++)
        {
            temp = A[i];
            for (j = i; j >= increment; j -= increment)
            {
                if (temp < A[j - increment]) A[j] = A[j - increment];
                else break;
            }
            A[j] = temp;
        }
    }
}

void shell_sort_sedgewick(int A[], int N)
{
    int i, j, increment;
    int temp;

    int qindex = 27;
    for (increment = sedgewick_queue[qindex]; increment > 0; increment = sedgewick_queue[--qindex])
    {
        if (increment < N)
        {
            for (i = increment; i<N; i++)
            {
                temp = A[i];
                for (j = i; j >= increment; j -= increment)
                {
                    if (temp < A[j - increment]) A[j] = A[j - increment];
                    else break;
                }
                A[j] = temp;
            }
        }
    }
}

void shell_sort_hibbard(int A[], int N)
{
    int i, j, increment;
    int temp;

    for (increment = N / 2 - 1; increment > 0; increment = (increment + 1) / 2 -1)
    {
        for (i = increment; i<N; i++)
        {
            temp = A[i];
            for (j = i; j >= increment; j -= increment)
            {
                if (temp < A[j - increment]) A[j] = A[j - increment];
                else break;
            }
            A[j] = temp;
        }
    }
}

int is_sorted(int A[], int N)
{
    int i;
    for (i = 1; i < N; i++) {
        if (A[i] < A[i - 1]) return 0;
    }
    return 1;
}

#define LeftChild(i) (2 * (i) + 1)

static void perc_down(int A[], int i, int N)
{
    int child;
    int temp;

    for (temp = A[i]; LeftChild(i) < N; i = child)
    {
        child = LeftChild(i);
        if (child != N - 1 && A[child + 1] > A[child])
            child++;
        if (temp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = temp;
}

void heap_sort(int A[], int N)
{
    int i;
    int temp;

    for (i = N / 2; i >= 0; i--) //Build Heap
        perc_down(A, i, N);
    for (i = N - 1; i > 0; i--)
    {
        temp = A[i];
        A[i] = A[0];
        A[0] = temp;

        perc_down(A, 0, i);
    }
}

static void merge(int A[], int tempArray[], int left_pos, int right_pos, int right_end)
{
    int i , left_end, num, temp_pos;

    left_end = right_pos - 1;
    temp_pos = left_pos;
    num = right_end - left_pos + 1;

    //compare and copy elements into temporary array.
    while (left_pos <= left_end && right_pos <= right_end)
    {
        if (A[left_pos] <= A[right_pos] )
            tempArray[temp_pos++] = A[left_pos++];
        else
            tempArray[temp_pos++] = A[right_pos++];
    }

    //copy the rest of left
    while (left_pos <= left_end)
        tempArray[temp_pos++] = A[left_pos++];
    //copy the rest of right
    while (right_pos <= right_end)
        tempArray[temp_pos++] = A[right_pos++];

    //copy back
    for (i = 0; i < num; i++, right_end--)
        A[right_end] = tempArray[right_end];
}

static void merge_sort_with_range(int A[], int temp[], int left, int right)
{
    int center = (left + right) / 2;

    if (left < right)
    {
        merge_sort_with_range(A, temp, left, center);
        merge_sort_with_range(A, temp, center + 1, right);
        merge(A, temp, left, center + 1, right);
    }
}

void merge_sort(int A[], int N)
{
    int *temp = malloc(N * sizeof(int));
    if (temp != NULL)
    {
        merge_sort_with_range(A, temp, 0, N - 1);
        free(temp);
    }
    else
    {
        fprintf(stderr, "No space in heap!");
    }
}

static void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
static int median3(int A[], int left, int right)
{
    int center = (left + right) / 2;

    if ( A[left] > A[center] ) swap(&A[left], &A[center]);

    if ( A[left] > A[right] ) swap(&A[left], &A[right]);

    if ( A[center] > A[right] ) swap(&A[center], &A[right]);
    
    swap( &A[center], &A[right - 1]);
    return A[right - 1];
}

static void QSort(int A[], int start, int end)
{
    int i, j;
    int pivot;

    if (start + 3 <= end)
    {
        pivot = median3(A, start, end);
        i = start;
        j = end - 1;
        while(1)
        {
            while(A[++i] < pivot);
            while(A[--j] > pivot);

            if (i < j)
                swap(&A[i], &A[j]);
            else
                break;
        }
        swap(&A[i], &A[end - 1]);

        QSort(A, start, i - 1);
        QSort(A, i + 1, end);
    }
    else
        insertionSort(A + start, end - start + 1);
}

void QuickSort(int A[], int N)
{
    QSort(A, 0, N-1);
}

