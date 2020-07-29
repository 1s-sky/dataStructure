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
	//초기화
	lp->head->next = lp->tail;
	lp->tail->next = lp->tail;
	lp->size = 0;

	return TRUE; 
}


BOOL addFirst(List *lp, char* data)
{
	Node* np;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node)); //새 노드 생성
	if (np != NULL) {                       //새 노드 생성 성공 시
		 strcpy(np->data, data);                    //새 노드의 data 저장
		np->next = lp->head->next;          //새 노드의 next 설정
		lp->head->next = np;                //head node 뒤에 새 노드 연결
		++lp->size;                         //리스트 size 증가
	}
	else { return FALSE; }                  //새 노드 생성 실패 시
	return TRUE; 
}

BOOL addLast(List *lp, char* data)
{
	Node* np;
	Node* btp;
	
	if (lp == NULL) { return FALSE; }
	np = (Node*)malloc(sizeof(Node));    //새 노드 생성
	if (np != NULL) {                          //새 노드 생성 성공 시
		strcpy(np->data, data);                       //새 노드의 data 저장
		btp = lp->head;
		while (btp->next != lp->tail) {
			btp = btp->next;
		}
		btp->next = np;                        //tail node 앞에 새 노드 연결
		np->next = lp->tail;                   //새 노드의 next 설정
		++lp->size;                            //리스트 size 증가
	}
	else { return FALSE; }                     //새 노드 생성 실패 시

	return TRUE; // return 값을 적절히 수정하세요.
}


void displayList(List *lp)
{
	Node* curp;
	size_t tot_length = 0;   //단어의 길이 누적변수 size_t-unsigned 정수형
	int i = 0;

	if (lp == NULL) { return; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		i++;
		printf("%d번째 단어 : %s\n", i, curp->data);
		tot_length += strlen(curp->data);
		curp = curp->next;
	}
	printf("\n전체 단어의 개수 : %d\t", lp->size);
	printf("평균단어길이 : %.2lf" , (double)tot_length/lp->size);
	
	return;
}


Node * searchNode(List *lp, char* data)
{
	Node* curp;

	if (lp == NULL) { return NULL; }
	if (lp->size == 0) { return NULL; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		if (strcmp(curp->data, data) == 0) {  //같으면 0을 return
			return curp;               // 찾았을 시
		}
		else { curp = curp->next; }    // 다음 칸 검색
	}
	return NULL;                       // 못 찾았을 시
}

BOOL removeNode(List *lp, char* data)
{
	Node* delp;
	Node* btp;

	if (lp == NULL) { return FALSE; }
	delp = searchNode(lp, data);      //삭제 할 data 검색
	if (delp != NULL) {
		btp = lp->head;               //삭제할 data의 바로 전 노드 검색
		while (btp->next != delp) {
			btp = btp->next;
		}
		btp->next = delp->next;       //list 연결
		free(delp);                   //메모리 해제
		--lp->size;                   //size 감소

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
	
	while (curp != lp->tail) {     //data가 들어있는 메모리 해제
		nextp = curp->next;
		free(curp);
		curp = nextp;
	}

	free(lp->head);                //더미노드 해제
	free(lp->tail);

	lp->head = lp->tail = NULL;    //메모리 정리
	lp->size = 0;

	return;
}

BOOL dataFileLode(List* lp) {
	FILE* fp;
	char word[80];
	Node* resp;       //searchNode return 값 저장

	fp = fopen("d:\\data\\flower.txt", "rt");
	if (fp == NULL) return FALSE;

	while (fscanf(fp, "%s", word) != EOF) {
		resp = searchNode(lp, word);
		if (resp == NULL) addLast(lp, word);  //없으면 등록
	}
	fclose(fp);
	return TRUE;
}