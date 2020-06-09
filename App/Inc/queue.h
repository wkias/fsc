#include <stdlib.h>
#define QUEUE_MAXSIZE 50
typedef struct Queue
{
    int data[QUEUE_MAXSIZE];
    int front; //队首指针
    int rear;  //队尾指针
} Queue;

Queue init_queue();
int is_empty(Queue q);
int enqueue(Queue *q, int x);
int dequeue(Queue *q, int *y);
void queue_demo();
