// DS HW3 no.2
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct node {
	element data;
	struct node *link;
}Node;

// �޸� ���� �Ҵ��� �̿��ؼ� ���ο� ��� ����
Node *create_node(element item) {

	Node *p = NULL;

	p = (Node *)malloc(sizeof(Node));

	// Error check
	if (p == NULL) {
		printf("Memory Allocation Failed!\n");
		exit(1);
	}

	p->data = item;
	p->link = NULL;

	return p;
}

// ����Ʈ�� �� �տ� value ���� ��带 ���� �� �߰�
Node *add(Node *head, element item) {

	Node *p = create_node(item);
	Node *temp = head;

	if (head == NULL)
	{
		// ���� ������ ����� ��ũ ���� ����Ʈ ù��° ��� �ּ� ������ �Ҵ�
		p->link = head;

		// ���� ������ ����� �ּ� ������ head ���� ����
		head = p;

		return head;
	}
	else 
	{
		while (temp->link != NULL)
		{
			if (temp->link->data >= item)
			{
				p->link = temp->link;
				temp->link = p;

				return head;
			}
			temp = temp->link;
		}
		if (temp->data >= item)
		{
			p->link = temp->link;
			temp->link = p;

			return head;
		}
		else
		{
			temp->link = p;
		}
		
		return head;
	}
	return NULL;
}

// ����Ʈ�� Ư�� ��� ���� ����!
Node *delete(Node *head, element item) {

	Node *temp = head;
	Node *temp2;

	// Check if list is empty
	if (head == NULL) {
		printf("List is empty!\n");
		exit(1);
	}

	while (temp->link != NULL)
	{
		if (temp->link->data == item)
		{
			temp2 = temp->link;
			temp->link = temp->link->link;
			free(temp2);

			return head;
		}
		temp = temp->link;
	}
	return NULL;
}

void print_list(Node *head) {

	Node *temp = head;
	
	while (temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->link;
	}
	printf("NULL\n");

	return;
}


Node *clear(Node *head)
{
	Node *temp = head;
	Node *temp2;

	if (temp->link == temp)
	{
		free(temp);
		head = NULL;

		return head;
	}
	else
	{
		while (temp->link != NULL)
		{
			temp2 = temp;
			temp = temp->link;
			free(temp2);
		}
		free(temp);
		head = NULL;

		return head;
	}
	return NULL;
}

int is_in_list(Node *head, element item)
{
	Node *temp = head;

	if (head == NULL) {
		printf("List is empty!\n");
		exit(1);
	}

	while (temp->link != NULL)
	{
		if (temp->data == item)
		{
			return TRUE;
		}
		temp = temp->link;
	}
	if (temp->data == item)
	{
		return TRUE;
	}
	return FALSE;
}

unsigned int get_length(Node *head)
{
	int temp = 0;
	Node *tempnd = head;

	while (tempnd != NULL)
	{
		temp++;
		tempnd = tempnd->link;
	}

	return temp;
}

int is_empty(Node *head)
{
	if (head == NULL)
	{
		return TRUE;
	}
	return FALSE;
}


int main(void) {

	Node *head = NULL;

	int getNum;
	int inputNum = 0;

	printf("Menu: 1. add, 2. delete, 3. clear, 4. is_in_list, 5. is_empty, 6.quit\n");

	while (1)
	{
		getNum = getch();

		if (getNum == 49)
		{// add
			printf("Input_add: ");
			scanf("%d", &inputNum);
			head = add(head, inputNum);
			print_list(head);
			printf("len: %d\n", get_length(head));
		}
		else if (getNum == 50)
		{// delete
			printf("Input_delete: ");
			scanf("%d", &inputNum);
			head = delete(head, inputNum);
			print_list(head);
			printf("len: %d\n", get_length(head));
		}
		else if (getNum == 51)
		{// clear
			head = clear(head);
			printf("Clear\n");
		}
		else if (getNum == 52)
		{// is in list
			printf("Input_is in list: ");
			scanf("%d", &inputNum);
			if (is_in_list(head, inputNum))
			{
				printf("%d (��)�� �ֽ��ϴ�.\n", inputNum);
			}
			else
			{
				printf("%d (��)�� �����ϴ�.\n", inputNum);
			}
		}
		else if (getNum == 53)
		{
			if (is_empty(head))
			{
				printf("list is empty\n");
			}
			else
			{
				printf("list is not empty\n");
			}
		}
		else if (getNum == 54)
		{
			break;
		}
	}

	return 0;
}