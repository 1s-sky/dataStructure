#include "arrayStack.h"
#include <stdio.h>
#include <malloc.h>
/*----------------------------------------------------------------------------------
Function name	: createStack - ������ ũ���� ������ �����ϴ� �Լ�
Parameters		: sp - ���ð��� ����ü�� �ּ�
				  size - ������ ũ��
Returns			: ���� - TRUE / ���� - FALSE
----------------------------------------------------------------------------------*/
BOOL createStack(Stack *sp, int size)
{
	if (sp == NULL) { return FALSE; }

	sp->stack = (int*)malloc(sizeof(int) * size);
	if (sp->stack != NULL) {
		sp->top = 0;
		sp->size = size;
		return TRUE;
	}
	else { return FALSE; }
}
/*-----------------------------------------------------------------------------------
Function name	: isStackFull - ������ �� ���ִ��� �˻�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ������ �� �������� TRUE, �ƴϸ� FALSE ����
-----------------------------------------------------------------------------------*/
BOOL isStackFull(Stack *sp)
{
	if (sp == NULL) { return FALSE; }
	if (sp->size == sp->top) { return TRUE; }
	else { return FALSE; }  // ���ϰ��� �������ּ���.
}
/*-----------------------------------------------------------------------------------
Function name	: isStackEmpty - ������ ������ ����ִ��� �˻�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ������ ������ ��������� TRUE, �ƴϸ� FALSE ����
-----------------------------------------------------------------------------------*/
BOOL isStackEmpty(Stack *sp)
{
	if (sp == NULL) { return FALSE; }
	if (sp->top == 0) { return TRUE; }
	else { return FALSE; }  // ���ϰ��� �������ּ���.
}
/*--------------------------------------------------------------------------------------
Function name	: push - ���ÿ� ������ �ϳ��� ������
Parameters		: sp - ���ð��� ����ü�� �ּ�
inData - ���ÿ� ������ ������
Returns			: ���������� �����ϸ� TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL push(Stack *sp, int inData)
{
	if (sp == NULL) { return FALSE; }
	if (isStackFull(sp)) { return FALSE; }
	else {
		sp->stack[sp->top] = inData;
		sp->top++;
		return TRUE;
	}
}
/*--------------------------------------------------------------------------------------
Function name	: pop - ���ÿ��� ������ �ϳ��� ����
Parameters		: sp - ���ð��� ����ü�� �ּ�
popData -  ���� �����͸� ������ �������� �ּ�
Returns			: ���������� ������ TRUE, �����ϸ� FALSE ����
--------------------------------------------------------------------------------------*/
BOOL pop(Stack * sp, int *popData)
{
	if (sp == NULL) { return FALSE; }
	if (isStackEmpty(sp)) { return FALSE; }
	else {
		sp->top--;
		*popData = sp->stack[sp->top];
		return TRUE;
	}
}
/*--------------------------------------------------------------------------------------
Function name	: printStack - ������ ��� ������ ���(pop�ϸ� ������ ������� ���)
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void printStack(const Stack* sp)
{
	int i = sp->top;
	if (sp == NULL) { return; }
	while(i != 0) {
		printf("%5d\n", sp->stack[--i]);
	}
	printf("\n");
	return;
}
/*--------------------------------------------------------------------------------------
Function name	: destroyStack -  ���� �Ҹ� �Լ�
Parameters		: sp - ���ð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void destroyStack(Stack *sp)
{
	if (sp == NULL) { return; }
	if (sp->stack != NULL) {
		free(sp->stack);
	}
	sp->size = 0;
	sp->stack = NULL;
	sp->top = 0;
	return;
}
