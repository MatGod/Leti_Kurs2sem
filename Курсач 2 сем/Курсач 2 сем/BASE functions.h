#include "AUTHOR functions.h"

BASE *getBaseFromKeyboard() {
	BASE *base = (BASE*)calloc(1, sizeof(BASE));
	unsigned kol;
	AUTHOR *author = NULL, *lastAuthor = NULL;
	system("cls");
	printf("������� ���������� ������������: ");
	kol = strToUnsigned(getStr());
	for (unsigned i = 1; i <= kol; i++) {
		author = getAuthorFromKeyboard();
		if (author != NULL) {
			lastAuthor = author;
			if (i == 1) {
				base->authors = author;
				lastAuthor = author;
			}
			else {
				lastAuthor->next = author;
				lastAuthor = lastAuthor->next;
			}
		}
		else {
			printf("������. ���������� �������� ������������ - %d.\n", i - 1);
			if (i == 1) {
				free(base);
				base = NULL;
			}
			break;
		}
	}
	return base;
}
//��������

BASE *getBaseFromFile(FILE *file) {
	BASE *base = (BASE*)calloc(1, sizeof(BASE));
	FILE *authorFile = NULL;
	char *authorAdress = NULL;
	unsigned kol;
	AUTHOR *author = NULL, *lastAuthor = NULL;
	system("cls");
	kol = strToUnsigned(getStrFromFile(file));
	for (unsigned i = 1; i <= kol; i++) {
		authorAdress = getStrFromFile(file);
		authorFile = fopen(authorAdress, "r");
		if (authorFile != NULL) {
			author = getAuthorFromFile(authorFile);
			if (author != NULL) {
				lastAuthor = author;
				if (i == 1) {
					base->authors = author;
					lastAuthor = author;
				}
				else {
					lastAuthor->next = author;
					lastAuthor = lastAuthor->next;
				}
			}
			else {
				printf("������. ���������� �������� ������������ - %d.\n", i - 1);
				if (i == 1) {
					free(base);
					base = NULL;
				}
				break;
			}
		}
		else {
			printf("������ �������� ����� %s.\n", authorAdress);
		}
	}
	return base;
}
//��������

BASE *getBase() {
	BASE *base = NULL;
	char choise;
	FILE *file;
	do {
		system("cls");
		puts("������� ������� � ��������������� ������� ������:");
		puts("(1) - ������� ���� �������.");
		puts("(2) - ������� ���� �� ������ �����.");
		choise = _getch();
		switch (choise) {
		case '1': {
			base = getBaseFromKeyboard();
			break;
		}
		case '2': {
			do {
				system("cls");
				puts("������� ���� � �����, �� ������ �������� ��������� ����.");
				file = fopen(getStr(), "r");
				if (file == NULL) {
					if (fileNull() == false) {
						break;
					}
				}
			} while (file == NULL);
			if (file != NULL) {
				base = getBaseFromFile(file);
				fclose(file);
			}
			break;
		}
		}
	} while ((choise < 49) || (choise > 50));
	if (base == NULL) {
		puts("������ ���� �� �������.");
	}
	return base;
}
//��������

void printBase(BASE *base) {

}

BASE *deleteAuthorFromBase(BASE *base) {
	return base;
}

BASE *deleteBase(BASE *base) {
	return base;
}

void addAuthorToBase(BASE *base) {
	
}