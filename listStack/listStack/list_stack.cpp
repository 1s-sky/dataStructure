#include "listStack.h"
#include <stdio.h>
#include <malloc.h>
/*--------------------------------------------------------------------------------------
Function name	: createStack - ��ũ�帮��Ʈ�� �����Ǵ� ���� ���� �Լ�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ���� - TRUE / ���� - FALSE
--------------------------------------------------------------------------------------*/
BOOL createStack(Stack *sp)
{
	if (sp == NULL) { return FALSE; }
	
	sp->head = (Snode*)calloc(1, sizeof(Snode));
	if (sp->head == NULL) { return FALSE; }
	
	sp->tail = (Snode*)calloc(1, sizeof(Snode));
	if (sp->tail == NULL) {
		free(sp->head);
		return FALSE;
	}
	sp->head->next = sp->tail;
	sp->tail->next = sp->tail;

	return TRUE; 
	
}
/*--------------------------------------------------------------------------------------
Function name	: isStackEmpty() - ������ ����ִ°� �˻�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ������ ��������� TRUE ����, ������� ������ FALSE ����
--------------------------------------------------------------------------------------*/
BOOL isStackEmpty(const Stack *sp)
{
	if (sp == NULL) return FALSE;

	if (sp->head->next == sp->tail) return TRUE;
   	else return FALSE;  
}
/*--------------------------------------------------------------------------------------
Function name	: push() - ���ÿ� ������ �ϳ��� ������
Parameters		: sp - ���ð��� ����ü�� �ּ�
				  pushData  - ���ÿ� ������ ������
Returns			: ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL push(Stack *sp, int pushData)
{
	Snode* np;
	if (sp == NULL) return FALSE;

	np = (Snode*)calloc(1, sizeof(Snode));
	if (np == NULL) return FALSE;
	
	np->next = sp->head->next;
	np->data = pushData;
	sp->head->next = np;

   	return TRUE;  // ���ϰ��� �������ּ���
}
/*--------------------------------------------------------------------------------------
Function name	: pop() - ���ÿ��� ������ �ϳ��� ����
Parameters		: sp - ���ð��� ����ü�� �ּ�
popData - ���� �����͸� ������ �������� �ּ�
Returns			: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL pop(Stack *sp, int *popData)
{
	Snode* delp;
	if (sp == NULL) return FALSE;

	if (isStackEmpty(sp)) return FALSE;
	else {
		*popData = sp->head->next->data;
		delp = sp->head->next;
		sp->head->next = sp->head->next->next;
		free(delp);
		return TRUE;
	}
}
/*--------------------------------------------------------------------------------------
Function name	: printStack - ������ ��� ������ ���(pop�ϸ� ������ ������� ���)
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void printStack(const Stack *sp)
{
	Snode* curp;
	if (sp == NULL) return;

	if (isStackEmpty(sp)) {
		printf("Stack�� ����ֽ��ϴ�.\n");
	}
	curp = sp->head->next;
	while (curp != sp->tail) {
		printf("%5d\n", curp->data);
		curp = curp->next;
	}
	printf("\n");
	return;
}
/*--------------------------------------------------------------------------------------
Function name	: destroyStack() - ���� �Ҹ� �Լ�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sp)
{
	Snode* curp;

	if (sp == NULL) return;

	while (sp->head->next != sp->tail) {
		curp = sp->head->next;
		sp->head->next = sp->head->next->next;
		free(curp);
	}
	free(sp->head);
	free(sp->tail);

	sp->head = sp->tail = NULL;
	return;
}
