#include <stdio.h>
#define MAX_QUEUE_SIZE 5 

typedef int element
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

init_queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

int main() {
	QueueType queue;

	init_queue(&queue);
}