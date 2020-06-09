#include "include.h"

Queue init_queue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
    {
        return;
    }
    q->rear = q->front = 0;
    return *q;
}

int is_empty(Queue q)
{
    return (q.front == q.rear ? 1 : 0);
}
int enqueue(Queue *q, int x)
{
    if ((q->rear + 1) % QUEUE_MAXSIZE == q->front)
    {
        return 0;
    }
    q->rear = (q->rear + 1) % QUEUE_MAXSIZE;
    q->data[q->rear] = x;
    return 1;
}
int dequeue(Queue *q, int *y)
{
    if (q->rear == q->front)
    {
        return 0;
    }
    *y = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAXSIZE;
    return 1;
}

void queue_demo()
{
    int y = 0;
    Queue q = init_queue();
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    dequeue(&q, &y);
}
