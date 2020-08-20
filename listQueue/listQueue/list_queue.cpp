#include <stdio.h> 
#include <malloc.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
Function name	: createQueue - 큐 초기화 함수
Parameters		: qp - 큐 구조체의 주소
Returns			: 성공 - TRUE / 실패 - FALSE
--------------------------------------------------------------------------------------*/
BOOL createQueue(Queue * qp)
{
	if (qp == NULL) return FALSE;
	qp->head = (Node*)malloc(sizeof(Node));
	
	if (qp->head == NULL) {
		return FALSE;
	}
	qp->tail = (Node*)malloc(sizeof(Node));

	if (qp->tail == NULL) {
		free(qp->head);
		return FALSE;
		
	}
	else {
		qp->head->next = qp->tail;
		qp->tail->next = qp->tail;
		return TRUE;
	}
}
/*--------------------------------------------------------------------------------------
Function name	: isQueueEmpty - 큐가 비어있는가 검사
Parameters		: qp - 큐 구조체의 주소
Returns			: 완전히 비어있으면 TRUE 리턴, 비어있지 않으면 FALSE 리턴
--------------------------------------------------------------------------------------*/
BOOL isQueueEmpty(const Queue *qp)
{
	if (qp == NULL) return FALSE;
	if (qp->head->next == qp->tail)  return TRUE; 
	else return FALSE;
}
/*--------------------------------------------------------------------------------------
Function name	: enqueue - 큐에 데이터 하나를 저장함
Parameters		: qp - 큐 구조체의 주소
				  enqueData - 큐에 저장할 데이터
Returns			: 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
BOOL enqueue(Queue * qp, int enqueData)
{
	Node* curp;
	Node* btp = qp->head;
	if (qp == NULL) return FALSE;
	curp = (Node*)malloc(sizeof(Node));
	if (curp == NULL) return FALSE;
	
	while (btp->next != qp->tail) {
		btp = btp->next;
	}
	btp->next = curp;
	curp->next = qp->tail;
	curp->data = enqueData;
	return TRUE;
}
/*--------------------------------------------------------------------------------------
Function name	: dequeue - 큐에서 데이터 하나를 꺼냄
Parameters		: qp - 큐 구조체의 주소
				  dequeData - 꺼낸 데이터를 저장할 기억공간의 주소
Returns			: 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
BOOL dequeue(Queue * qp, int * dequeData)
{
	Node* curp;
	if (qp == NULL) return FALSE;
	if (isQueueEmpty(qp)) return FALSE;
	else {
		*dequeData = qp->head->next->data;
		curp = qp->head->next;
		qp->head->next = qp->head->next->next;
		free(curp);
		return TRUE;
	}
}
/*--------------------------------------------------------------------------------------
Function name	: printQueue - 큐 내의 모든 데이터를 출력 함
Parameters		: qp - 큐 구조체의 주소
Returns			: 없음
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qp)
{
	Node* curp;
	if (qp == NULL) return;

	if (isQueueEmpty(qp)) {
		printf("Queue가 비어있습니다.\n");
		return;
	}
	
	curp = qp->head->next;
	while (curp != qp->tail) {
		printf("%d\n", curp->data);
		curp = curp->next;
	}
	printf("\n");
	return;
}
/*--------------------------------------------------------------------------------------
Function name	: destroyQueue - 큐 소멸 함수
Parameters		: qp - 큐 구조체의 주소
Returns			: 없음
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qp)
{
	Node* curp = qp->head->next;
	if (qp == NULL) return;

	while (curp == qp->tail) {
		qp->head->next = curp->next;
		free(curp);
		curp = qp->head->next;
	}
	free(qp->head);
	free(qp->tail);
	qp->head = qp->tail = NULL;
	return;
}
