#include "doublyLinkedlist.h"
#include <stdio.h>  // printf(), scanf()
#include <stdlib.h>  // malloc(), free()
/*----------------------------------------------------------------------------------
Function name	: createList - 연결 리스트 초기화
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
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

	return TRUE; // 리턴값을 적절히 수정하세요.
}
/*----------------------------------------------------------------------------------
Function name	: addFirst - head node 뒤에 node 추가(역순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: addLast - tail node 앞에 새 node 추가(정순 저장)
Parameters		: lp - 리스트 관리 구조체의 주소
				  data - 추가할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: displayList - 리스트 내의 모든 데이터 출력
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
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
Function name	: searchNode - data와 일치하는 첫 번째 node 검색
Parameters		: lp - 리스트 관리 구조체의 주소
data - 검색할 데이터
Returns			: 성공 - 검색된 노드의 주소 / 실패 - NULL pointer
----------------------------------------------------------------------------------*/
Node * searchNode(List *lp, int data)
{
	Node* curp;

	if (lp == NULL) { return NULL; }
	curp = lp->head->next;
	while (curp != lp->tail) {
		if (curp->data == data) {
			return curp;               // 찾았을 시
		}
		else { curp = curp->next; }    // 다음 칸 검색
	}
	return NULL;                       // 못 찾았을 시
}
/*----------------------------------------------------------------------------------
Function name	: removeNode - data와 일치하는 첫 번째 노드 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
data - 삭제할 데이터
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: sortList - 노드 정렬(오름차순)
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
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
Function name	: destroyList - 리스트 내의 모든 노드(head, tail 노드 포함)를 삭제
Parameters		: lp - 리스트 관리 구조체의 주소
Returns			: 없음
----------------------------------------------------------------------------------*/
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
