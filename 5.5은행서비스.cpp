#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "queue.h"

int main() {
	QueueType queue;
	int sec = 60; //교재에서는 min으로 함.
	int total_wait = 0;
	int service_time = 0;
	int service_customer;
	int total_customer = 0;

	init_queue(&queue);
	srand((unsigned)time(NULL));
	for (int clock = 0; clock < sec; clock++) {
		Sleep(1000);
		printf("현재시간 = %d\n", clock);
		if (rand() % 10 < 3) { // 고객만들기 
			
			element customer;
			customer.id = total_customer++;
			customer.arrival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer);
			service_customer = customer.id;
			printf("고객 번호 %d번이 %d초에 들어옵니다. 업무처리시간 = %d초\n", customer.id, customer.arrival_time, customer.service_time);
		}
		if (service_time > 1) { //누군가에게 서비스중임.
			printf("고객 %d 업무처리중입니다.\n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id; //업무중인 인원이 없을 때 바로 업무를 볼 수 있게 해준다.
				service_time = customer.service_time;
				printf("고객 %d번이 %d초에 업무를 시작합니다. 대기시간은 %d초입니다.\n", customer.id, clock, clock - customer.arrival_time);
				total_wait += clock - customer.arrival_time;
			}
		}
	}
	printf("전체 대기시간 = %d초\n", total_wait);
	return 0;
}