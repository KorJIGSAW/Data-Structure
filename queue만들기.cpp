#include <stdio.h>
#define MAX_QUEUE_SIZE 5 

typedef int element
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

void enqueue(QueueType* q, element item) {
	//overflow check!
	//원형큐이므로 나머지 연산을 해주어야한다.
	/*
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	*/
	q->data[++(q->rear) % MAX_QUEUE_SIZE] = item;
}

element dequeue(QueueType* q) {
	//underflow check!
	/*
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->data[q->front] = item;
	*/
	return q->data[++(q->front) % MAX_QUEUE_SIZE];
}

int main() {
	QueueType queue;

	init_queue(&queue);
	enqueue(&queue, 1);
	element item = dequeue(&queue);
}