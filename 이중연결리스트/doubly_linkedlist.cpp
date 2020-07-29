#include "doublyLinkedlist.h"
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()
/*----------------------------------------------------------------------------------
Function name	: createList - ���� ����Ʈ �ʱ�ȭ
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL createList(List *lp)
{
	if (lp == NULL) { return FALSE; }

	lp->head = (Node*)malloc(sizeof(Node));
	if (lp->head == NULL) {
		return FALSE;
	}

	lp->tail = (Node*)malloc(sizeof(Node));
	if (lp->tail == NULL) {
		free(lp->head);
		return FALSE;
	}
	
	lp->head->next = lp->tail;
	lp->head->prev = lp->head;
	lp->tail->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->size = 0;

	return TRUE; // ���ϰ��� ������ �����ϼ���.
}
/*----------------------------------------------------------------------------------
Function name	: addFirst - head node �ڿ� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addFirst(List *lp, int data)
{
	Node* newp;
	if (lp == NULL) { return FALSE; }

	newp = (Node*)malloc(sizeof(Node));
	if (newp != NULL) { 
		newp->prev = lp->head;
		newp->next = lp->head->next;
		newp->data = data;
		lp->head->next->prev = newp;
		lp->head->next = newp;
		++lp->size;
		return TRUE;
	}
	else { return FALSE; }
}
/*----------------------------------------------------------------------------------
Function name	: addLast - tail node �տ� �� node �߰�(���� ����)
Parameters		: lp - ����Ʈ ���� ����ü�� �ּ�
				  data - �߰��� ������
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL addLast(List *lp, int data)
{
	Node* newp;
	if (lp == NULL) { return FALSE; }

	newp = (Node*)malloc(sizeof(Node));
	if (newp != NULL) {
		newp->data = data;
		newp->prev = lp->tail->prev;
		newp->next = lp->tail;
		lp->tail->prev->next = newp;
		lp->tail->prev = newp;
		++lp->size;
		return TRUE;
	}
	else { return FALSE; }
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
	if (lp == NULL) { return FALSE; }
	
	delp = searchNode(lp, data);
	if (delp != NULL) {
		delp->prev->next = delp->next;
		delp->next->prev = delp->prev;
		free(delp);
		--lp->size;
		return TRUE;
	}
	else { return TRUE; }
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
