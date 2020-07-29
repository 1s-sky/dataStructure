#include "arrayStack.h"
#include <stdio.h>
#include <malloc.h>
/*----------------------------------------------------------------------------------
Function name	: createStack - 지정된 크기의 스택을 생성하는 함수
Parameters		: sp - 스택관리 구조체의 주소
				  size - 스택의 크기
Returns			: 성공 - TRUE / 실패 - FALSE
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
Function name	: isStackFull - 스택이 꽉 차있는지 검사
Parameters		: sp - 스택관리 구조체의 주소
Returns			: 스택이 꽉 차있으면 TRUE, 아니면 FALSE 리턴
-----------------------------------------------------------------------------------*/
BOOL isStackFull(Stack *sp)
{
	if (sp == NULL) { return FALSE; }
	if (sp->size == sp->top) { return TRUE; }
	else { return FALSE; }  // 리턴값은 수정해주세요.
}
/*-----------------------------------------------------------------------------------
Function name	: isStackEmpty - 스택이 완전히 비어있는지 검사
Parameters		: sp - 스택관리 구조체의 주소
Returns			: 스택이 완전히 비어있으면 TRUE, 아니면 FALSE 리턴
-----------------------------------------------------------------------------------*/
BOOL isStackEmpty(Stack *sp)
{
	if (sp == NULL) { return FALSE; }
	if (sp->top == 0) { return TRUE; }
	else { return FALSE; }  // 리턴값은 수정해주세요.
}
/*--------------------------------------------------------------------------------------
Function name	: push - 스택에 데이터 하나를 저장함
Parameters		: sp - 스택관리 구조체의 주소
inData - 스택에 저장할 데이터
Returns			: 성공적으로 저장하면 TRUE, 실패하면 FALSE 리턴
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
Function name	: pop - 스택에서 데이터 하나를 꺼냄
Parameters		: sp - 스택관리 구조체의 주소
popData -  꺼낸 데이터를 저장할 기억공간의 주소
Returns			: 성공적으로 꺼내면 TRUE, 실패하면 FALSE 리턴
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
Function name	: printStack - 스택의 모든 데이터 출력(pop하면 나오는 순서대로 출력)
Parameters		: sp - 스택관리 구조체의 주소
Returns			: 없음
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
Function name	: destroyStack -  스택 소멸 함수
Parameters		: sp - 스택관리 구조체의 주소
Returns			: 없음
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
