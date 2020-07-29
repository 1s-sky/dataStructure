// 단어 수 세기_단일연결리스트.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <string.h>
#include "singlyLinkedlist.h"
#pragma warning (disable : 4996)

int main()
{
    List list;		     // 리스트관리 구조체 변수
    
    
    BOOL bres;

    bres = createList(&list);   //리스트 생성 및 초기화
    if (bres == FALSE) {
        printf("리스트 초기화 error\n");
        return 0;
    }

    bres = dataFileLode(&list);
    if (bres == FALSE) {
        printf("file open error\n");
        return 0;
    }
    sortList(&list);
    displayList(&list);
    destroyList(&list);
    
    return 0;
}


