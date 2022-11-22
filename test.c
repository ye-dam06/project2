#include <stdio.h>
#include <string.h>
#include "book.h"
#define DEBUG

extern int listSize;

#ifdef DEBUG
char Testadd(_stBook list[], char num);
char TestRm(_stBook list[], char num);

char Testadd(_stBook list[], char num) {	// 테스트용 도서 추가
	int i = num;
	char buf[30];	// 정수->문자열 변환 위한 임시 buffer
	sprintf_s(buf, sizeof(buf), "%d번째 책(test)", i + 1);	// 정수를 문자열로 변환해 변수에 저장해주는 함수
	strcpy_s(list[i].title, sizeof(list[i].title), buf);
	strcpy_s(list[i].author, sizeof(list[i].author), "테스트");
	list[i].price = 10000;
	list[i].page = 100;
	list[i].date.year = 1;
	list[i].date.month = 1;
	list[i].date.day = 1;

	i++;

	return i;
}

char TestRm(_stBook list[], char num) {	// 테스트용 도서 삭제
	memset(&list[num - 1], 0, sizeof(_stBook));	// 삭제
	num--;	// 데이터 개수 줄임
	return num;
}

#endif