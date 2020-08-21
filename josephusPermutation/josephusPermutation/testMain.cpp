#include "listQueue.h"
#include <stdio.h>
#pragma warning (disable : 4996)
//--------------------------------------------------------------------------------
//   main()
//--------------------------------------------------------------------------------
int main()
{
	Queue que; /* 큐생성*/
	int N, M;   /* N : 인원수, M : 간격 수 */
	int i;
	int getData;   /* deueue한 데이터 저장 변수 */

	createQueue(&que); /* 큐 생성 및 초기화*/

	printf("N(인원수)와 M(간격수)를 입력하시오 (M<=N) : ");
	scanf("%d %d", &N, &M);

	for (i = 1; i <= N; i++)
		enqueue(&que, i);
	printf("(%d,%d)조세퍼스의 순열 : ", N, M);
	while (!isQueueEmpty(&que)) {
		for (int j = 0; j < M - 1; j++) {
			if(dequeue(&que, &getData)==TRUE)
				enqueue(&que, getData);
		}
		if (dequeue(&que, &getData) == TRUE) 
			printf("%d ", getData);
		
	}

	destroyQueue(&que);
	return 0;
}

