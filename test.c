#include <stdio.h>
#include <string.h>
#include "book.h"
#define DEBUG

extern int listSize;

#ifdef DEBUG
char Testadd(_stBook list[], char num);
char TestRm(_stBook list[], char num);

char Testadd(_stBook list[], char num) {	// �׽�Ʈ�� ���� �߰�
	int i = num;
	char buf[30];	// ����->���ڿ� ��ȯ ���� �ӽ� buffer
	sprintf_s(buf, sizeof(buf), "%d��° å(test)", i + 1);	// ������ ���ڿ��� ��ȯ�� ������ �������ִ� �Լ�
	strcpy_s(list[i].title, sizeof(list[i].title), buf);
	strcpy_s(list[i].author, sizeof(list[i].author), "�׽�Ʈ");
	list[i].price = 10000;
	list[i].page = 100;
	list[i].date.year = 1;
	list[i].date.month = 1;
	list[i].date.day = 1;

	i++;

	return i;
}

char TestRm(_stBook list[], char num) {	// �׽�Ʈ�� ���� ����
	memset(&list[num - 1], 0, sizeof(_stBook));	// ����
	num--;	// ������ ���� ����
	return num;
}

#endif