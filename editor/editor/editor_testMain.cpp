#include "liststack.h"
#include <stdio.h>
#pragma warning (disable : 4996)

int main()
{
	Stack lstk, rstk;     /* 왼쪽, 오른쪽 스택 생성*/
	FILE *fp;
	char ch;
	int i;
	int cmdCnt;  /* 명령어 개수 저장 변수 */

	createStack(&lstk); /* 스택초기화*/
	createStack(&rstk); /* 스택초기화*/

	fp = fopen("d:\\data\\editor1.txt", "rt");
	if(fp==NULL){
		printf("파일 오픈 에러!!\n");
		getchar();
		return 1;
	}
	//첫줄 읽기
	while ((ch = fgetc(fp)) != '\n')
		push(&lstk, ch);
	
	//명령어 개수 읽기
	fscanf(fp, " %d", &cmdCnt);
	
	//명령어 수행
	for (i = 0; i < cmdCnt; i++) 
	{
		//명렁어 읽어오기
		fscanf(fp, " %c", &ch);
		switch (ch)
		{
		case 'L':    //커서 왼쪽으로 이동
			if (pop(&lstk, &ch)) {  //if 체크 필수!
				push(&rstk, ch);
			}
			break;
		
		case 'D':    //커서 오른쪽으로 이동 
			if (pop(&rstk, &ch)) {
				push(&lstk, ch);
			}
			break;
		
		case 'B':    //커서 왼쪽의 문자 삭제
			pop(&lstk, &ch);
			break;
		
		case 'P':    //P뒤의 문자 커서 앞에 추가
			fscanf(fp, " %c", &ch);
			push(&lstk, ch);
			break;
		}
		
	}

	//출력하기
	while(!isStackEmpty(&lstk))
	{
		char temp;
		if (pop(&lstk, &temp)) {
			push(&rstk, temp);
		}
	}
	printStack(&rstk);
	//데이터 해제 필수!
	destroyStack(&lstk);
	destroyStack(&rstk);

	fclose(fp);
	return 0;
}
