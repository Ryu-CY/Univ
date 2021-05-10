#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 7
typedef char element;
typedef struct { // ť Ÿ��
	element* data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
//void error(char *message)
//{
//	fprintf(stderr, "%s\n", message);
//	exit(1);
//}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType *q)
{
	//printf("QUEUE(front=%s rear=%c) = ", q->front, q->rear);
	if (!is_empty(q)) {
			int i = q->front;
			do {
				i = (i + 1) % (MAX_QUEUE_SIZE);
				printf("%s | ", q->data[i]);
				if (i == q->rear)
					break;
			} while (i != q->front);
		}
	printf("\n");
}

// ���� �Լ�
void enqueue(QueueType *q, element* item)
{
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element* dequeue(QueueType *q)
{
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element* peek(QueueType *q)
{
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

void hotPotato(QueueType* q, int num)
{
	QueueType tempQ;
	char* temp;
	int a = MAX_QUEUE_SIZE;
	for (int i = 0; i < num; i++)
	{
		temp = peek(q);
		dequeue(q);
		enqueue(q, temp);
		queue_print(q);
		if ((i == num - 1) && (a > 2))
		{
			enqueue(&tempQ, peek(q));
			dequeue(q);
			a--;
			i = 0;
		}
	}
	printf("\n�ƿ� �� �÷��̾� ���\n");
	queue_print(&tempQ);
	printf("\n������ ���� �÷��̾�: ");
	queue_print(q);
}

int main(void)
{
	QueueType queue;
	int a = 0;

	printf("Num: ");
	scanf("%d", &a);

	init_queue(&queue);

	enqueue(&queue, "Brad");
	enqueue(&queue, "Kent");
	enqueue(&queue, "Jane");
	enqueue(&queue, "Susan");
	enqueue(&queue, "David");
	enqueue(&queue, "Bill");
	
	hotPotato(&queue, a);

	return 0;
}