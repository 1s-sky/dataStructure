#include "listQueue.h"
#include <stdio.h>
#pragma warning (disable : 4996)
//--------------------------------------------------------------------------------
//   main()
//--------------------------------------------------------------------------------
int main()
{
	Queue que; /* ť����*/
	int N, M;   /* N : �ο���, M : ���� �� */
	int i;
	int getData;   /* deueue�� ������ ���� ���� */

	createQueue(&que); /* ť ���� �� �ʱ�ȭ*/

	printf("N(�ο���)�� M(���ݼ�)�� �Է��Ͻÿ� (M<=N) : ");
	scanf("%d %d", &N, &M);

	for (i = 1; i <= N; i++)
		enqueue(&que, i);
	printf("(%d,%d)�����۽��� ���� : ", N, M);
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

