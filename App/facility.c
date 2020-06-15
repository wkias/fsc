#include "include.h"
typedef float32_t ElementType;
#define LeftChild(i) (2 * (i) + 1)

void swap(float32_t *a, float32_t *b)
{
    float32_t temp = *a;
    *a = *b;
    *b = temp;
}

void perc_down(float32_t A[], int i, int N)
{
    int child;
    ElementType Tmp;

    for (Tmp = A[i]; 2 * i + 1 < N; i = child)
    {
        child = 2 * i + 1;
        if (child != N - 1 && A[child + 1] > A[child])
            ++child;
        if (Tmp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = Tmp;
}

void heap_sort(float32_t A[], int N)
{
    int i;
    for (i = N / 2; i >= 0; --i)
        perc_down(A, i, N);
    for (i = N - 1; i > 0; --i)
    {
        swap(&A[0], &A[i]);
        perc_down(A, 0, i);
    }
}
