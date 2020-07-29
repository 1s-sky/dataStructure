#include "singlyLinkedlist.h"
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()
#include <string.h>
#pragma warning (disable : 4996)


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


BOOL addFirst(List *lp, char* data)
{
	Node* np;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node)); //�� ��� ����
	if (np != NULL) {                       //�� ��� ���� ���� ��
		 strcpy(np->data, data);                    //�� ����� data ����
		np->next = lp->head->next;          //�� ����� next ����
		lp->head->next = np;                //head node �ڿ� �� ��� ����
		++lp->size;                         //����Ʈ size ����
	}
	else { return FALSE; }                  //�� ��� ���� ���� ��
	return TRUE; 
}

BOOL addLast(List *lp, char* data)
{
	Node* np;
	Node* btp;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node));    //�� ��� ����
	if (np != NULL) {                          //�� ��� ���� ���� ��
		strcpy(np->data, data);                       //�� ����� data ����
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


void displayList(List *lp)
{
	Node* curp;
	size_t tot_length = 0;   //�ܾ��� ���� �������� size_t-unsigned ������
	int i = 0;

	if (lp == NULL) { return; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		i++;
		printf("%d��° �ܾ� : %s\n", i, curp->data);
		tot_length += strlen(curp->data);
		curp = curp->next;
	}
	printf("\n��ü �ܾ��� ���� : %d\t", lp->size);
	printf("��մܾ���� : %.2lf" , (double)tot_length/lp->size);
	
	return;
}


Node * searchNode(List *lp, char* data)
{
	Node* curp;

	if (lp == NULL) { return NULL; }
	if (lp->size == 0) { return NULL; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		if (strcmp(curp->data, data) == 0) {  //������ 0�� return
			return curp;               // ã���� ��
		}
		else { curp = curp->next; }    // ���� ĭ �˻�
	}
	return NULL;                       // �� ã���� ��
}

BOOL removeNode(List *lp, char* data)
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

void sortList(List *lp)
{
	Node* curp;
	Node* nextp;
	char temp[80];

	if (lp == NULL) { return; }

	curp = lp->head->next;

	while (curp->next != lp->tail) {
		nextp = curp->next;
		
		while (nextp != lp->tail) {
		
			if (strcmp(curp->data, nextp->data) > 0) {   //data swap
				strcpy(temp, curp->data);
				strcpy(curp->data, nextp->data);
				strcpy(nextp->data, temp);
			}
			nextp = nextp->next;
		}
		curp = curp->next;
	}
	
	return;
}

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

BOOL dataFileLode(List* lp) {
	FILE* fp;
	char word[80];
	Node* resp;       //searchNode return �� ����

	fp = fopen("d:\\data\\flower.txt", "rt");
	if (fp == NULL) return FALSE;

	while (fscanf(fp, "%s", word) != EOF) {
		resp = searchNode(lp, word);
		if (resp == NULL) addLast(lp, word);  //������ ���
	}
	fclose(fp);
	return TRUE;
}