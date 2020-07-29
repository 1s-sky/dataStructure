#include "singlyLinkedlist.h"
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()
#pragma warning (disable : 4996)

/*----------------------------------------------------------------------------------
Function name	: createList - ���� ����Ʈ ���� �� �ʱ�ȭ
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL createList(List *lp)
{
	if (lp == NULL) { return FALSE; }
	//head
	lp->head = (Node*)malloc(sizeof(Node));
	if (lp->head == NULL) return FALSE;
	//tail
	lp->tail = (Node*)malloc(sizeof(Node));
	if (lp->tail == NULL) {
		free(lp->head);
		return FALSE;
	}
	//�ʱ�ȭ
	lp->head->next = lp->tail;
	lp->tail->next = lp->tail;
	lp->size = 0;

	return TRUE; 
}

/*----------------------------------------------------------------------------------
Function name	: addFirst - head node �ڿ� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addFirst(List *lp, int data)
{
	Node* np;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node)); //�� ��� ����
	if (np != NULL) {                       //�� ��� ���� ���� ��
		np->data = data;                    //�� ����� data ����
		np->next = lp->head->next;          //�� ����� next ����
		lp->head->next = np;                //head node �ڿ� �� ��� ����
		++lp->size;                         //����Ʈ size ����
	}
	else { return FALSE; }                  //�� ��� ���� ���� ��
	return TRUE; 
}
/*----------------------------------------------------------------------------------
Function name	: addLast - tail node �տ� �� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addLast(List *lp, int data)
{
	Node* np;
	Node* btp;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node));    //�� ��� ����
	if (np != NULL) {                          //�� ��� ���� ���� ��
		np->data = data;                       //�� ����� data ����
		btp = lp->head;
		while (btp->next != lp->tail) {
			btp = btp->next;
		}
		btp->next = np;                        //tail node �տ� �� ��� ����
		np->next = lp->tail;                   //�� ����� next ����
		++lp->size;                            //����Ʈ size ����
	}
	else { return FALSE; }                     //�� ��� ���� ���� ��

	return TRUE; // return ���� ������ �����ϼ���.
}

/*----------------------------------------------------------------------------------
Function name	: displayList - ����Ʈ ���� ��� ������ ���
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void displayList(List *lp)
{
	Node* curp;

	if (lp == NULL) { return; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		printf("%8d\n", curp->data);
		curp = curp->next;
	}
	printf("\n");

	return;
}

/*----------------------------------------------------------------------------------
Function name	: searchNode - data�� ��ġ�ϴ� ù ��° node �˻�
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �˻��� ������
Returns			: ���� - �˻��� ����� �ּ� / ���� - NULL pointer
----------------------------------------------------------------------------------*/
Node * searchNode(List *lp, int data)
{
	Node* curp;

	if (lp == NULL) { return NULL; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		if (curp->data == data) {
			return curp;               // ã���� ��
		}
		else { curp = curp->next; }    // ���� ĭ �˻�
	}
	return NULL;                       // �� ã���� ��
}
/*----------------------------------------------------------------------------------
Function name	: removeNode - data�� ��ġ�ϴ� ù ��° ��� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
data - ������ ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL removeNode(List *lp, int data)
{
	Node* delp;
	Node* btp;

	if (lp == NULL) { return FALSE; }
	delp = searchNode(lp, data);      //���� �� data �˻�
	if (delp != NULL) {
		btp = lp->head;               //������ data�� �ٷ� �� ��� �˻�
		while (btp->next != delp) {
			btp = btp->next;
		}
		btp->next = delp->next;       //list ����
		free(delp);                   //�޸� ����
		--lp->size;                   //size ����

		return TRUE;
	}
	else { return FALSE; }
}
/*----------------------------------------------------------------------------------
Function name	: sortList - ��� ����(��������)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void sortList(List *lp)
{
	Node* curp;
	Node* nextp;
	int temp;

	if (lp == NULL) { return; }

	curp = lp->head->next;

	while (curp->next != lp->tail) {
		nextp = curp->next;
		
		while (nextp != lp->tail) {
		
			if (curp->data > nextp->data) {   //data swap
				temp = curp->data;
				curp->data = nextp->data;
				nextp->data = temp;
			}
			nextp = nextp->next;
		}
		curp = curp->next;
	}
	
	return;
}
/*----------------------------------------------------------------------------------
Function name	: destroyList - ����Ʈ ���� ��� ���(head, tail ��� ����)�� ����
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ����
----------------------------------------------------------------------------------*/
void destroyList(List *lp)
{
	Node* curp;
	Node* nextp;

	if (lp == NULL) { return; }

	curp = lp->head->next;
	
	while (curp != lp->tail) {     //data�� ����ִ� �޸� ����
		nextp = curp->next;
		free(curp);
		curp = nextp;
	}

	free(lp->head);                //���̳�� ����
	free(lp->tail);

	lp->head = lp->tail = NULL;    //�޸� ����
	lp->size = 0;

	return;
}

