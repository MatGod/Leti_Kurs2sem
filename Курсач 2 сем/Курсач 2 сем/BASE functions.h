#include "AUTHOR functions.h"

AUTHOR *getLastAuthor(BASE *base) {
	AUTHOR *author = base->authors;
	while (author->next != NULL) {
		author = author->next;
	}
	return author;
}
//��������

BASE *deleteBase(BASE *base) {
	AUTHOR *author = NULL;
	if (base->authors != NULL) {
		author = base->authors->next;
	}
	else {
		while (base->authors != NULL) {
			base->authors = deleteAuthor(base->authors);
			base->authors = author;
			if (author != NULL) {
				author = author->next;
			}
		}
		puts("���� �������.");
	}
	return NULL;
}
//��������

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
			printf("������. ���������� ������� �������� ������������ - %d.\n", i - 1);
			if (i == 1) {
				base = deleteBase(base);
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
	if (base != NULL) {
		FILE *authorFile = NULL;
		char *authorAdress = NULL;
		AUTHOR *author = NULL, *lastAuthor = NULL;
		system("cls");
		do {
			authorAdress = getStrFromFile(file);
			if (authorAdress[0] != '\0') {
				authorFile = fopen(authorAdress, "r");
				if (authorFile != NULL) {
					author = getAuthorFromFile(authorFile);
					if (author != NULL) {
						lastAuthor = author;
						if (base->authors == NULL) {
							base->authors = author;
							lastAuthor = author;
						}
						else {
							lastAuthor->next = author;
							lastAuthor = lastAuthor->next;
						}
					}
					else {
						printf("������. �� ������� ������ ����������� �� %s.\n", authorAdress);
					}
				}
				else {
					printf("������ �������� ����� %s.\n", authorAdress);
				}
			}
		} while (authorAdress[0] != '\0');
		if (base->authors == NULL) {
			base = deleteBase(base);
			puts("�� ������� ������ �� ������ �����������. ���� �� �������.");
		}
	}
	else {
		puts("������. ������������ ������.");
	}
	return base;
}
//��������

BASE *getBase(BASE *base) {
	if (base != NULL) {
		base = deleteBase(base);
	}
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
	else {
		puts("���� ������� �������.");
	}
	return base;
}
//��������

void printBase(BASE *base) {
	system("cls");
	if (base == NULL) {
		puts("���� �����.");
	}
	else {
		AUTHOR *author = base->authors;
		unsigned i = 1;
		while (author != NULL) {
			printf("%d - %s\n", i, author->name);
			i++;
			author = author->next;
		}
	}
}
//��������

unsigned notAuthorInBase() {
	char choise;
	do {
		system("cls");
		puts("����������� � ����� ������� ���. ������ ������ �����?");
		puts("(1) - ��.");
		puts("(2) - ���.");
		choise = _getch();
		switch (choise) {
		case '1': {
			return 0;
			break;
		}
		case '2': {
			return 1;
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 50);
}
//��������

BASE *deleteAuthorFromBase(BASE *base) {
	AUTHOR *author;
	AUTHOR *prevAuthor;
	unsigned num;
	do {
		printBase(base);
		author = base->authors;
		prevAuthor = NULL;
		system("cls");
		puts("������� ����� �����������, �������� ������ �������.");
		num = strToUnsigned(getStr());
		if (num > 0) {
			for (unsigned i = 1; i < num; i++) {
				prevAuthor = author;
				author = author->next;
			}
		}
		if (num == 0 || author == NULL) {
			num = notAuthorInBase();
		}
		else {
			if (prevAuthor != NULL) {
				prevAuthor->next = author->next;
			}
			else {
				base->authors = author->next;
			}
			author = deleteAuthor(author);
			break;
		}
	} while (num == 0);
	if (base->authors == NULL) {
		base = deleteBase(base);
		puts("�� ���� ����� ������������ �����������. ���� �����.");
	}
	return base;
}
//��������

void addAuthorToBase(BASE *base) {
	AUTHOR *author = getLastAuthor(base);
	author->next = getAuthor();
}
//��������

BASE *changeAuthorInBase(BASE *base) {
	AUTHOR *author;
	AUTHOR *prevAuthor;
	AUTHOR *nextAuthor;
	unsigned num;
	do {
		printBase(base);
		author = base->authors;
		nextAuthor = author->next;
		prevAuthor = NULL;
		puts("������� ����� �����������, �������� ������ ����������/��������.");
		num = strToUnsigned(getStr());
		if (num > 0) {
			for (unsigned i = 1; i < num; i++) {
				prevAuthor = author;
				author = author->next;
				nextAuthor = author->next;
			}
		}
		if (num == 0 || author == NULL) {
			num = notAuthorInBase();
		}
		else {
			author = changeAuthor(author);
			if (author == NULL) {
				if (prevAuthor != NULL) {
					prevAuthor->next = nextAuthor;
				}
				else {
					base->authors = nextAuthor;
				}
			}
			break;
		}
	} while (num == 0);
	if (base->authors == NULL) {
		base = deleteBase(base);
		puts("�� ���� ����� ������������ �����������. ���� �����.");
	}
	return base;
}
//��������

BASE *changeBase(BASE *base) {
	if (base == NULL) {
		puts("���� �����.");
	}
	else {
		char choise;
		do {
			system("cls");
			puts("��� �� ������ ������� � �����?");
			puts("(1) - �������� ������ ������������ � ����");
			puts("(2) - �������� �����������.");
			puts("(3) - ����������/�������� ������� �� ������������.");
			puts("(4) - ������� �����������.");
			choise = _getch();
			switch (choise)
			{
			case '1': {
				printBase(base);
				break;
			}
			case '2': {
				addAuthorToBase(base);
				break;
			}
			case '3': {
				base = changeAuthorInBase(base);
				break;
			}
			case '4': {
				base = deleteAuthorFromBase(base);
				break;
			}
			default: {
				system("cls");
				puts("������ � ����� ������� ���!");
				system("pause");
				break;
			}
			}
		} while (choise < 49 || choise > 52);
	}
	return base;
}
//��������