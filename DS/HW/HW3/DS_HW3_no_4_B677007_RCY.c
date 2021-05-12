// DS HW3 no.4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 100	        // ������ �ִ� ũ��
#define TRUE 1
#define FALSE 0

clock_t start, finish;
double duration;

typedef int element;		        // �������� �ڷ���
element  stack[MAX_STACK_SIZE];     // 1���� �迭


int  top = -1;                      // �������� ����			

// ���� ���� ���� 
int is_empty()
{
	if (top == -1)
		return TRUE;
	else
		return FALSE;
}

// ��ȭ ���� ���� 
int is_full()
{
	if (top == MAX_STACK_SIZE - 1)
		return TRUE;
	else
		return FALSE;
}

// ������ �߰� 
void push(element item)
{
	if (is_full()) {
		fprintf(stderr, "Stack is full!!\n");
		exit(1);
	}
	else {
		top++;
		stack[top] = item;
		//printf("Item %d is pushed.\n", item);
	}

	return;
}

// ������ ���� 
element pop()
{
	element temp;

	if (is_empty()) {
		fprintf(stderr, "Stack is empty!!\n");
		exit(1);
	}
	else {
		temp = stack[top];
		top--;
		//printf("Item %d is popped.\n", temp);
		return temp;
	}
}

int main(void)
{
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		push(1);
		pop();
	}
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f sec \n", duration);

	return 0;
}