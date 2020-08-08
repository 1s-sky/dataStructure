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
	fscanf(fp, " %c", &cmdCnt);
	
	//명령어 수행
	for (int i = 0; i < cmdCnt; i++) 
	{
		//명렁어 읽어오기
		fscanf(fp, " %c", &ch);
		if (ch == 'L') {       //커서 왼쪽으로 이동
			char temp;
			if (pop(&lstk, &temp)) {
				push(&rstk, temp);
			}
		}
		else if (ch == 'D') {  //커서 오른쪽으로 이동
			char temp;
			if (pop(&rstk, &temp)) {
				push(&lstk, temp);
			}
		}
		else if (ch == 'B') {  //커서 왼쪽의 문자 삭제
			char temp;
			pop(&lstk, &temp);
		}
		else if (ch == 'P') {  //P뒤의 문자 커서 앞에 추가
			char temp;
			fscanf(fp, " %c", &temp);
			push(&lstk, temp);
		}
		else {
			printf("잘못된 입력입니다.");
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

	fclose(fp);
	return 0;
}
