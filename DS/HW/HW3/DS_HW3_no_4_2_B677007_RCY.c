// DS HW3 no.4-2
#include<stdio.h>
#include<stdlib.h>
#include <time.h>


clock_t start, finish;
double duration;


typedef int element;
typedef struct node{
    element data;
    struct node *link;
}Node;

Node *top;

// �޸� ���� �Ҵ��� �̿��ؼ� ���ο� ��� ����
Node *create_node(element value){

    Node *p = NULL;

    p = (Node *)malloc(sizeof(Node));

    // Error check
    if (p == NULL){
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    p->data = value;
    p->link = NULL;

    return p;
}

// ����Ʈ�� �� �տ� value ���� ��带 ���� �� �߰�
Node *insert_first(Node *head, element value){
    
    Node *p = create_node(value);

    // ���� ������ ����� ��ũ ���� ����Ʈ ù��° ��� �ּ� ������ �Ҵ�
    p->link = head;

    // ���� ������ ����� �ּ� ������ head ���� ����
    head = p;

    return head;
}
Node *insert_last(Node *head, element value)
{
	Node *p = create_node(value);

	if (head == NULL)
	{
		head = p;
		top = p;
	}
	else
	{
		top->link = p;
		top = p;
	}
	return head;
}

// ����Ʈ�� ù��° ��� ����
Node *delete_first(Node *head){

    Node *temp = NULL;

    // Check if list is empty
    if (head == NULL){
        printf("List is empty!\n");
        exit(1);
    }

    // ù��° ���(��, ������ ���)�� �ּ� ���� temp�� ����
    temp = head;

    // head �������� ���� �� ��° ����� �ּҰ����� ����
    head = head->link;

    free(temp);

    return head;
}

Node *delete_last(Node * head)
{
	Node *temp = head;

	// Check if list is empty
	if (head == NULL) {
		printf("List is empty!\n");
		exit(1);
	}
	if (temp == top)
	{
		temp = NULL;
	}
	else
	{
		while (temp->link != top)
		{
			temp = temp->link;
		}

		temp->link = NULL;
		top = temp;
	}
	

	return head;
}

void print_list(Node *head){

    Node *temp = head;

    while (temp!=NULL){
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");

    return;
}

int main(void){

    Node *head = NULL;

	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		head = insert_last(head, 10);
		//print_list(head);
		head = delete_last(head);
	}
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f sec \n", duration);

    return 0;
}