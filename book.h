#ifndef __BOOK_H__
#define __BOOK_H__
#define _CRT_SECURE_NO_WARNINGS

#define SIZE 20

typedef struct {
	char year;
	char month;
	char day;
}_stDate;

typedef struct {
	char title[30];
	int price;
	char author[10];
	int page;
	_stDate date;
} _stBook;

char DispMenu(char num);
char CountData(_stBook list[]);
char AddBook(_stBook list[], char num);
void PrintBook(_stBook list[], char num);
void SortMenu(_stBook list[], char num);
void SelectionSort(_stBook list[], char num, char select);
char* SearchBook(_stBook list[], char num);
void PrintSearch(_stBook list[], char i);
char RmBook(_stBook list[], char num);
char Rm(_stBook list[], char num, int listnum);
void SearchBookforRm(_stBook list[], char num, char* sr);


#endif