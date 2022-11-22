#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define DEBUG
#define _CRT_SECURE_NO_WARNINGS


void GotoXY(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


char DispMenu(char num) {
	char menu;

	printf("------------------------------------------------------------------------------\n");
	printf("|                                                                            |\n");
	printf("|                           도서 검색 프로그램                               |\n");
	printf("|                                              (현재 데이터 개수 : %2d)       |\n", num);
	printf("|----------------------------------MENU--------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  1. 도서 추가                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  2. 도서 삭제                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  3. 도서 정렬                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. 도서 검색                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. 도서 확인                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  6. 종료                                                                   |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   원하는 메뉴를 입력하세요 [ ]\b\b");
	scanf_s("%hhd", &menu);
	return menu;
}


char CountData(_stBook list[]) {
	char cnt = 0;
	for (int i = 0; i < SIZE; i++) {
		if (list[i].title[0] != 0) cnt++;
	}
	return cnt;
}


char AddBook(_stBook list[], char num) {
	// GotoXY 버전
	int i = num;
	char temp[100] = { 0, };
	for (; i < SIZE; i++) {
		char chk;
		printf("------------------------------------------------------------------------------\n\n");
		printf("   도서 제목을 입력하세요: ");
		printf("\n\n   도서 가격을 입력하세요: ");
		printf("\n\n   도서 저자를 입력하세요: ");
		printf("\n\n   도서 페이지를 입력하세요: ");
		printf("\n\n   도서 발행연도를 입력하세요 : __ __ __ (yy-mm-dd)");
		printf("\n\n------------------------------------------------------------------------------\n");

		GotoXY(27, 2);
		scanf_s(" %[^\n]s", temp, sizeof(temp));	// 공백포함해서 입력받음
		if (strlen(temp) > sizeof(list[i].title) - 1) {	// 입력받은문자열의 길이+\0이 배열의 길이를 초과하는 경우 다시 입력받음
			printf("   너무 긴 문자열을 입력하셨습니다. 처음부터 다시 입력해 주세요.\n");
			i--;
			continue;
		}
		else strcpy_s(list[i].title, sizeof(list[i].title), temp);

		GotoXY(27, 4);
		scanf_s("%d", &list[i].price);

		GotoXY(27, 6);
		scanf_s(" %[^\n]s", temp, sizeof(temp));
		if (strlen(temp) > sizeof(list[i].author) - 1) {
			printf("   너무 긴 문자열을 입력하셨습니다. 처음부터 다시 입력해 주세요.\n");
			i--;
			continue;
		}
		else strcpy_s(list[i].author, sizeof(list[i].author), temp);

		GotoXY(29, 8);
		scanf_s("%d", &list[i].page);

		GotoXY(32, 10);
		scanf_s("%02hhd %02hhd %02hhd", &list[i].date.year, &list[i].date.month, &list[i].date.day); // 0포함 입력받음

		printf("\n\n   계속 입력하려면[1] 메뉴로 돌아가려면[0]를 입력하세요 [ ]\b\b");
		scanf_s("%hhd", &chk);
		if (chk == 0) {
			i++;
			return i;
		}
		system("cls");
	}
	printf("   입력 가능한 데이터 개수를 초과하였습니다. ");
	system("pause");
	return i;
}


void PrintBook(_stBook list[], char num) {
	printf("------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");
	for (int i = 0; i < num; i++) {
		printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i + 1, list[i].title, list[i].price, list[i].author, list[i].page, list[i].date.year, list[i].date.month, list[i].date.day);
	}
	printf("------------------------------------------------------------------------------\n");
}


void SortMenu(_stBook list[], char num) {
	char select;
	printf("|----------------------------------------------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  무엇으로 정렬하시겠습니까?                                                |\n");
	printf("|                                                                            |\n");
	printf("|  1. 가격 순                                                                |\n");
	printf("|                                                                            |\n");
	printf("|  2. 발행연도 순                                                            |\n");
	printf("|                                                                            |\n");
	printf("|  3. 페이지 순                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. 도서명 순                                                              |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   원하는 메뉴를 입력하세요 [ ]\b\b");
	scanf_s("%hhd", &select);
	SelectionSort(list, num, select);
}


void SelectionSort(_stBook list[], char num, char select) {
	int i, j, min;
	_stBook temp;
	_stBook justforsort[SIZE];	// 원본값이 훼손되지 않도록 임시 구조체배열 생성

	memmove(justforsort, list, sizeof(_stBook[SIZE]));	// 구조체 복사

	for (i = 0; i < num - 1; i++) {
		min = i;
		if (select == 1) {	// 가격 정렬
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].price < justforsort[min].price) min = j;
			}
		}
		else if (select == 2) {	// 발행연도 정렬
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].date.year < justforsort[min].date.year) min = j;	//	년
				else if (justforsort[j].date.year == justforsort[min].date.year) {
					if (justforsort[j].date.month < justforsort[min].date.month) min = j;	// 월
					else if (justforsort[j].date.month == justforsort[min].date.month) {
						if (justforsort[j].date.day < justforsort[min].date.day) min = j;	// 일
					}
				}
			}
		}
		else if (select == 3) { // 페이지 정렬
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].page < justforsort[min].page) min = j;
			}
		}
		else if (select == 4) { // 도서명 정렬
			for (j = i + 1; j < num; j++) {
				if (strcmp(justforsort[j].title, justforsort[min].title) < 0) min = j;
			}
		}
		temp = justforsort[i];
		justforsort[i] = justforsort[min];
		justforsort[min] = temp;
	}
	system("cls");
	PrintBook(justforsort, num);	// 출력함수 호출
}


char* SearchBook(_stBook list[], char num) {
	char keyword[100] = { 0, };
	char chk = 0;
	static char array[SIZE] = { 0, };

	for (int i = 0; i < num; i++) {
		array[i] = 0;
	}

	printf("------------------------------------------------------------------------------\n");
	printf("   검색어를 입력하세요.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %[^\n]s", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");
	for (int i = 0; i < num; i++) {
		if (strstr(list[i].title, keyword) != NULL) {	// 키워드로 검색하여 널이 아닌 경우 출력
			PrintSearch(list, i);
			array[chk] = i + 1;
			chk++;	// 검색결과의 갯수와 열번호 저장
		}
	}
	if (chk == 0) printf("   검색 결과가 없습니다.\n");
	printf("------------------------------------------------------------------------------\n");
	return array;
}


void PrintSearch(_stBook list[], char i) {
	printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i + 1, list[i].title, list[i].price, list[i].author, list[i].page, list[i].date.year, list[i].date.month, list[i].date.day);
}


char RmBook(_stBook list[], char num) {
	char rmnum = 0;
	int i = 0;
	char chk = 0;
	printf("------------------------------------------------------------------------------\n");
	printf("   삭제하고자 하는 도서를 검색하세요\n");

	// 메모리 동적할당
	char* sr = (char*)calloc(num, sizeof(char));
	if (sr == NULL) {
		printf("메모리 할당에 실패하였습니다.");
		return 1;
	}
	// 검색함수 호출
	SearchBookforRm(list, num, sr);

	if (sr[0] == 0) {	// 검색 결과가 없을 때
		printf("\n   메뉴로 돌아갑니다......");
		system("pause");
	}
	else if (sr[1] == 0) {	// 검색 결과가 1개일 때
		num = Rm(list, num, sr[0]); // 삭제 함수 호출, 삭제할 번호는 1부터시작하는 번호로 넘겨줌
	}
	else {	// 검색 결과가 여러개 일 때
		printf("\n   삭제할 도서 번호를 입력해주세요 ... [  ]\b\b\b");
		scanf_s("%hhd", &rmnum);
		for (i = 0; i < num; i++) {
			if (sr[i] == rmnum && rmnum != 0) {
				num = Rm(list, num, rmnum);
				chk++;
				break;
			}
		}
		if (chk == 0) { // 검색리스트에 없는 다른 도서번호를 입력했을 때
			printf("\n   잘못 입력하셨습니다...");
			system("pause");
		}
	}

	free(sr);	// 메모리할당 해제

	return num;
}


char Rm(_stBook list[], char num, int listnum) {
	char chk = 0;
	printf("\n   정말 삭제하시겠습니까? Yes [1] / No [0] ... [ ]\b\b");
	scanf_s("%hhd", &chk);
	if (chk == 1) {
		memset(&list[listnum - 1], 0, sizeof(_stBook));	// 삭제
		for (int i = listnum - 1; i < num; i++) {
			memmove(&list[i], &list[i + 1], sizeof(_stBook));	// 삭제한곳부터 한칸씩 앞으로 땡겨서 정렬
		}
		num--;	// 데이터 개수 줄임
		printf("\n   삭제가 완료되었습니다...");
		system("pause");
		return num;
	}
	else {	// 1이 아닌 다른 숫자를 입력했을 때
		printf("\n   삭제하지 않고 메뉴로 돌아갑니다...");
		system("pause");
		return num;
	}
}


void SearchBookforRm(_stBook list[], char num, char* sr) {
	char keyword[100] = { 0, };
	char chk = 0;

	printf("\n   검색어를 입력하세요.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %[^\n]s", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");
	for (int i = 0; i < num; i++) {
		if (strstr(list[i].title, keyword) != NULL) {	// 키워드로 검색하여 널이 아닌 경우 출력
			PrintSearch(list, i);
			sr[chk] = i + 1;
			chk++;	// 검색결과의 갯수와 열번호 저장
		}
	}
	if (chk == 0) printf("   검색 결과가 없습니다.\n");
	printf("------------------------------------------------------------------------------\n");
}