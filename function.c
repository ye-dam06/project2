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
	printf("|                           ���� �˻� ���α׷�                               |\n");
	printf("|                                              (���� ������ ���� : %2d)       |\n", num);
	printf("|----------------------------------MENU--------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  1. ���� �߰�                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  2. ���� ����                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  3. ���� ����                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. ���� �˻�                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. ���� Ȯ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  6. ����                                                                   |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   ���ϴ� �޴��� �Է��ϼ��� [ ]\b\b");
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
	// GotoXY ����
	int i = num;
	char temp[100] = { 0, };
	for (; i < SIZE; i++) {
		char chk;
		printf("------------------------------------------------------------------------------\n\n");
		printf("   ���� ������ �Է��ϼ���: ");
		printf("\n\n   ���� ������ �Է��ϼ���: ");
		printf("\n\n   ���� ���ڸ� �Է��ϼ���: ");
		printf("\n\n   ���� �������� �Է��ϼ���: ");
		printf("\n\n   ���� ���࿬���� �Է��ϼ��� : __ __ __ (yy-mm-dd)");
		printf("\n\n------------------------------------------------------------------------------\n");

		GotoXY(27, 2);
		scanf_s(" %[^\n]s", temp, sizeof(temp));	// ���������ؼ� �Է¹���
		if (strlen(temp) > sizeof(list[i].title) - 1) {	// �Է¹������ڿ��� ����+\0�� �迭�� ���̸� �ʰ��ϴ� ��� �ٽ� �Է¹���
			printf("   �ʹ� �� ���ڿ��� �Է��ϼ̽��ϴ�. ó������ �ٽ� �Է��� �ּ���.\n");
			i--;
			continue;
		}
		else strcpy_s(list[i].title, sizeof(list[i].title), temp);

		GotoXY(27, 4);
		scanf_s("%d", &list[i].price);

		GotoXY(27, 6);
		scanf_s(" %[^\n]s", temp, sizeof(temp));
		if (strlen(temp) > sizeof(list[i].author) - 1) {
			printf("   �ʹ� �� ���ڿ��� �Է��ϼ̽��ϴ�. ó������ �ٽ� �Է��� �ּ���.\n");
			i--;
			continue;
		}
		else strcpy_s(list[i].author, sizeof(list[i].author), temp);

		GotoXY(29, 8);
		scanf_s("%d", &list[i].page);

		GotoXY(32, 10);
		scanf_s("%02hhd %02hhd %02hhd", &list[i].date.year, &list[i].date.month, &list[i].date.day); // 0���� �Է¹���

		printf("\n\n   ��� �Է��Ϸ���[1] �޴��� ���ư�����[0]�� �Է��ϼ��� [ ]\b\b");
		scanf_s("%hhd", &chk);
		if (chk == 0) {
			i++;
			return i;
		}
		system("cls");
	}
	printf("   �Է� ������ ������ ������ �ʰ��Ͽ����ϴ�. ");
	system("pause");
	return i;
}


void PrintBook(_stBook list[], char num) {
	printf("------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
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
	printf("|  �������� �����Ͻðڽ��ϱ�?                                                |\n");
	printf("|                                                                            |\n");
	printf("|  1. ���� ��                                                                |\n");
	printf("|                                                                            |\n");
	printf("|  2. ���࿬�� ��                                                            |\n");
	printf("|                                                                            |\n");
	printf("|  3. ������ ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. ������ ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   ���ϴ� �޴��� �Է��ϼ��� [ ]\b\b");
	scanf_s("%hhd", &select);
	SelectionSort(list, num, select);
}


void SelectionSort(_stBook list[], char num, char select) {
	int i, j, min;
	_stBook temp;
	_stBook justforsort[SIZE];	// �������� �Ѽյ��� �ʵ��� �ӽ� ����ü�迭 ����

	memmove(justforsort, list, sizeof(_stBook[SIZE]));	// ����ü ����

	for (i = 0; i < num - 1; i++) {
		min = i;
		if (select == 1) {	// ���� ����
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].price < justforsort[min].price) min = j;
			}
		}
		else if (select == 2) {	// ���࿬�� ����
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].date.year < justforsort[min].date.year) min = j;	//	��
				else if (justforsort[j].date.year == justforsort[min].date.year) {
					if (justforsort[j].date.month < justforsort[min].date.month) min = j;	// ��
					else if (justforsort[j].date.month == justforsort[min].date.month) {
						if (justforsort[j].date.day < justforsort[min].date.day) min = j;	// ��
					}
				}
			}
		}
		else if (select == 3) { // ������ ����
			for (j = i + 1; j < num; j++) {
				if (justforsort[j].page < justforsort[min].page) min = j;
			}
		}
		else if (select == 4) { // ������ ����
			for (j = i + 1; j < num; j++) {
				if (strcmp(justforsort[j].title, justforsort[min].title) < 0) min = j;
			}
		}
		temp = justforsort[i];
		justforsort[i] = justforsort[min];
		justforsort[min] = temp;
	}
	system("cls");
	PrintBook(justforsort, num);	// ����Լ� ȣ��
}


char* SearchBook(_stBook list[], char num) {
	char keyword[100] = { 0, };
	char chk = 0;
	static char array[SIZE] = { 0, };

	for (int i = 0; i < num; i++) {
		array[i] = 0;
	}

	printf("------------------------------------------------------------------------------\n");
	printf("   �˻�� �Է��ϼ���.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %[^\n]s", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
	printf("==============================================================================\n");
	for (int i = 0; i < num; i++) {
		if (strstr(list[i].title, keyword) != NULL) {	// Ű����� �˻��Ͽ� ���� �ƴ� ��� ���
			PrintSearch(list, i);
			array[chk] = i + 1;
			chk++;	// �˻������ ������ ����ȣ ����
		}
	}
	if (chk == 0) printf("   �˻� ����� �����ϴ�.\n");
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
	printf("   �����ϰ��� �ϴ� ������ �˻��ϼ���\n");

	// �޸� �����Ҵ�
	char* sr = (char*)calloc(num, sizeof(char));
	if (sr == NULL) {
		printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
		return 1;
	}
	// �˻��Լ� ȣ��
	SearchBookforRm(list, num, sr);

	if (sr[0] == 0) {	// �˻� ����� ���� ��
		printf("\n   �޴��� ���ư��ϴ�......");
		system("pause");
	}
	else if (sr[1] == 0) {	// �˻� ����� 1���� ��
		num = Rm(list, num, sr[0]); // ���� �Լ� ȣ��, ������ ��ȣ�� 1���ͽ����ϴ� ��ȣ�� �Ѱ���
	}
	else {	// �˻� ����� ������ �� ��
		printf("\n   ������ ���� ��ȣ�� �Է����ּ��� ... [  ]\b\b\b");
		scanf_s("%hhd", &rmnum);
		for (i = 0; i < num; i++) {
			if (sr[i] == rmnum && rmnum != 0) {
				num = Rm(list, num, rmnum);
				chk++;
				break;
			}
		}
		if (chk == 0) { // �˻�����Ʈ�� ���� �ٸ� ������ȣ�� �Է����� ��
			printf("\n   �߸� �Է��ϼ̽��ϴ�...");
			system("pause");
		}
	}

	free(sr);	// �޸��Ҵ� ����

	return num;
}


char Rm(_stBook list[], char num, int listnum) {
	char chk = 0;
	printf("\n   ���� �����Ͻðڽ��ϱ�? Yes [1] / No [0] ... [ ]\b\b");
	scanf_s("%hhd", &chk);
	if (chk == 1) {
		memset(&list[listnum - 1], 0, sizeof(_stBook));	// ����
		for (int i = listnum - 1; i < num; i++) {
			memmove(&list[i], &list[i + 1], sizeof(_stBook));	// �����Ѱ����� ��ĭ�� ������ ���ܼ� ����
		}
		num--;	// ������ ���� ����
		printf("\n   ������ �Ϸ�Ǿ����ϴ�...");
		system("pause");
		return num;
	}
	else {	// 1�� �ƴ� �ٸ� ���ڸ� �Է����� ��
		printf("\n   �������� �ʰ� �޴��� ���ư��ϴ�...");
		system("pause");
		return num;
	}
}


void SearchBookforRm(_stBook list[], char num, char* sr) {
	char keyword[100] = { 0, };
	char chk = 0;

	printf("\n   �˻�� �Է��ϼ���.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %[^\n]s", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
	printf("==============================================================================\n");
	for (int i = 0; i < num; i++) {
		if (strstr(list[i].title, keyword) != NULL) {	// Ű����� �˻��Ͽ� ���� �ƴ� ��� ���
			PrintSearch(list, i);
			sr[chk] = i + 1;
			chk++;	// �˻������ ������ ����ȣ ����
		}
	}
	if (chk == 0) printf("   �˻� ����� �����ϴ�.\n");
	printf("------------------------------------------------------------------------------\n");
}