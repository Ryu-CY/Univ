// �ڷᱸ�� HW3 no.3
#include<stdio.h>
#include<stdlib.h>

typedef char element;
typedef struct dnode {
	element *data;
	struct dnode *llink;
	struct dnode *rlink;
}DNode;

unsigned int countList(DNode *head)
{
	int temp = 0;
	DNode *tempnd = head;

	while (tempnd->rlink != NULL)
	{
		tempnd = tempnd->rlink;
		temp++;
	}
	temp -= 1;

	return temp;
}

// value ���� ���ο� ���� ����
DNode *create_node(const element *str) {
	DNode *p = NULL;

	p = (DNode *)malloc(sizeof(DNode));
	if (p == NULL) {   // �޸� �Ҵ� ����
		printf("Memory allocation failed!\n");
		exit(1);
	}
	p->data = str;
	p->llink = NULL;
	p->rlink = NULL;

	return p;
}

// ����Ʈ�� ó���� value �� �߰�
DNode *add(DNode *head, const element *str) {

	DNode *p = create_node(str);

	p->llink = head;
	p->rlink = head->rlink;
	head->rlink->llink = p;
	head->rlink = p;

	return head;
}

// ����Ʈ ���� ��� ����� �� ���
void print_list(DNode *head) {

	// temp�� ù��° ��带 ����Ŵ (���� ����� header �̿�)
	DNode *temp = head->rlink;

	// temp �� trailer ���� ��忡 �����ϸ� ������ ��������
	while (temp->rlink != NULL) {
		printf("%s -> ", temp->data);
		temp = temp->rlink;
	}
	printf("NULL\n");

	return;
}

DNode *search(DNode *head, const element *str)
{
	DNode *temp = head;

	while (temp->rlink != NULL)
	{
		if (temp->data == str)
		{
			return temp;
		}
		temp = temp->rlink;
	}
	return NULL;
}

DNode *remove_(DNode *head, DNode *p)
{
	DNode *temp = head;

	if (head == NULL)
	{
		printf("%List is empty!\n");
		exit(1);
	}

	while (temp->rlink != NULL)
	{
		if (temp->data == p->data)
		{
			temp->llink->rlink = temp->rlink;
			temp->rlink->llink = temp->llink;
			free(temp);
			return head;
		}
		temp = temp->rlink;
	}
	return NULL;
}

int main(void) {

	DNode header, trailer;

	header.llink = NULL;
	header.rlink = &trailer;
	trailer.llink = &header;
	trailer.rlink = NULL;

	DNode *head = &header;

	int getNum = 0;
	int searchNum = 0;
	int remove_Num = 0;
	char searchInput[50] = { 0 };
	printf("Menu: 1. add: asd.Apk, 2. add: qwe.Apk, 3. add: zxc.Apk, 4. search, 5. quit\n");

	while (1)
	{
		getNum = getch();

		if (getNum == 49)
		{// asd.Apk
			head = add(head, "asd.Apk");
			print_list(head);
			printf("Opned Applications: %d\n", countList(head));
		}
		else if (getNum == 50)
		{// qwe.Apk
			head = add(head, "qwe.Apk");
			print_list(head);
			printf("Opned Applications: %d\n", countList(head));
		}
		else if (getNum == 51)
		{// zxc.Apk
			head = add(head, "zxc.Apk");
			print_list(head);
			printf("Opned Applications: %d\n", countList(head));
		}
		else if (getNum == 52)
		{// search, remove
			printf("1. asd.Apk Ȯ��, 2. qwe.Apk Ȯ��, 3. zxc.Apk Ȯ��\n");
			searchNum = getch();
			if (searchNum == 49)
			{
				if (search(head, "asd.Apk"))
				{
					printf("Find: %s\n", search(head, "asd.Apk")->data);
					printf("Remove this data? 1. Yes, 2. No\n");
					remove_Num = getch();
					if (remove_Num == 49)
					{
						remove_(head, search(head, "asd.Apk"));
					}
					else if (remove_Num == 50)
					{
						printf("don't remove\n");
					}
				}
				else if (search(head, "asd.Apk") == NULL)
				{
					printf("ã������ Apk�� �������� �ʽ��ϴ�.\n");
				}
			}
			else if (searchNum == 50)
			{
				if (search(head, "qwe.Apk"))
				{
					printf("Find: %s\n", search(head, "qwe.Apk")->data);
					printf("Remove this data? 1. Yes, 2. No\n");
					remove_Num = getch();
					if (remove_Num == 49)
					{
						remove_(head, search(head, "qwe.Apk"));
					}
					else if (remove_Num == 50)
					{
						printf("don't remove\n");
					}
				}
				else if (search(head, "qwe.Apk") == NULL)
				{
					printf("ã������ Apk�� �������� �ʽ��ϴ�.\n");
				}
			}
			else if (searchNum == 51)
			{
				if (search(head, "zxc.Apk"))
				{
					printf("Find: %s\n", search(head, "zxc.Apk")->data);
					printf("Remove this data? 1. Yes, 2. No\n");
					remove_Num = getch();
					if (remove_Num == 49)
					{
						remove_(head, search(head, "zxc.Apk"));
					}
					else if (remove_Num == 50)
					{
						printf("don't remove\n");
					}
				}
				else if (search(head, "zxc.Apk") == NULL)
				{
					printf("ã������ Apk�� �������� �ʽ��ϴ�.\n");
				}
			}
		}
		else if (getNum == 53)
		{// quit
			return;
		}
	}

	return 0;
}