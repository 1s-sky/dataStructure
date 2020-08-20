#include <stdio.h> 
#include <malloc.h> 
#include "listQueue.h" 

/*--------------------------------------------------------------------------------------
Function name	: createQueue - ť �ʱ�ȭ �Լ�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
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
Function name	: isQueueEmpty - ť�� ����ִ°� �˻�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ������ ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
BOOL isQueueEmpty(const Queue *qp)
{
	if (qp == NULL) return FALSE;
	if (qp->head->next == qp->tail)  return TRUE; 
	else return FALSE;
}
/*--------------------------------------------------------------------------------------
Function name	: enqueue - ť�� ������ �ϳ��� ������
Parameters		: qp - ť ����ü�� �ּ�
				  enqueData - ť�� ������ ������
Returns			: ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
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
Function name	: dequeue - ť���� ������ �ϳ��� ����
Parameters		: qp - ť ����ü�� �ּ�
				  dequeData - ���� �����͸� ������ �������� �ּ�
Returns			: ���������� ������ TRUE, �����ϸ� FALSE ����
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
Function name	: printQueue - ť ���� ��� �����͸� ��� ��
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qp)
{
	Node* curp;
	if (qp == NULL) return;

	if (isQueueEmpty(qp)) {
		printf("Queue�� ����ֽ��ϴ�.\n");
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
Function name	: destroyQueue - ť �Ҹ� �Լ�
Parameters		: qp - ť ����ü�� �ּ�
Returns			: ����
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
