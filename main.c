#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#define DEBUG
#define _CRT_SECURE_NO_WARNINGS

int listSize = 10;


int main(void) {

	_stBook booklist[SIZE] = {
	{"모두의 딥러닝", 20000, "조태호", 300, {22,1,1}},
	{"혼자 공부하는 자바", 24000, "신용권", 708, {19,6,10}},
	{"윈도우 11 가이드북", 17100, "권순만", 432, {22,3,25}},
	{"파이썬 정복", 19800, "김상형", 508, {18,4,2}},
	{"코딩테스트 연습", 30600, "나동빈", 604, {20,8,5}},
	{"안드로이드 프로그래밍", 33000, "우재남", 580, {22,1,22}},
	{"가장 쉬운 유니티", 54000, "이제민", 1102, {22,2,1}},
	{"sql 정복", 35100, "김상형", 708, {21,5,1}},
	{"자바스크립트 입문",  16200, "고경희", 352, {21,11,1}},
	{"node.js 교과서", 32400, "조현영", 756, {20,7,25}},
	};

	char datanum = CountData(booklist);

	while (1) {
		char menu;
		system("cls");
		menu = DispMenu(datanum);
		system("cls");
		if (menu == 6) break;
		else if (menu == 1) datanum = AddBook(booklist, datanum);
		else if (menu == 2) datanum = RmBook(booklist, datanum);
		else if (menu == 3) {
			SortMenu(booklist, datanum);
			system("pause");
		}
		else if (menu == 4) {
			SearchBook(booklist, datanum);
			system("pause");
		}
		else if (menu == 5) {
			PrintBook(booklist, datanum);
			system("pause");
		}
		else {
			rewind(stdin);
			continue;
		}
	}
	return 0;
}