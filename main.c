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
	{"����� ������", 20000, "����ȣ", 300, {22,1,1}},
	{"ȥ�� �����ϴ� �ڹ�", 24000, "�ſ��", 708, {19,6,10}},
	{"������ 11 ���̵��", 17100, "�Ǽ���", 432, {22,3,25}},
	{"���̽� ����", 19800, "�����", 508, {18,4,2}},
	{"�ڵ��׽�Ʈ ����", 30600, "������", 604, {20,8,5}},
	{"�ȵ���̵� ���α׷���", 33000, "���糲", 580, {22,1,22}},
	{"���� ���� ����Ƽ", 54000, "������", 1102, {22,2,1}},
	{"sql ����", 35100, "�����", 708, {21,5,1}},
	{"�ڹٽ�ũ��Ʈ �Թ�",  16200, "�����", 352, {21,11,1}},
	{"node.js ������", 32400, "������", 756, {20,7,25}},
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