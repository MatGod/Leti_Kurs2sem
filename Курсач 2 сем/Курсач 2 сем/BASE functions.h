#include "AUTHOR functions.h"

BASE *getBaseFromKeyboard() {
	BASE *base = (BASE*)calloc(1, sizeof(BASE));
	unsigned kol;
	AUTHOR *author = NULL, *lastAuthor = NULL;
	system("cls");
	printf("Введите количество исполнителей: ");
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
			printf("Ошибка. Количество введённых исполнителей - %d.\n", i - 1);
			if (i == 1) {
				free(base);
				base = NULL;
			}
			break;
		}
	}
	return base;
}
//Работает

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
				printf("Ошибка. Количество введённых исполнителей - %d.\n", i - 1);
				if (i == 1) {
					free(base);
					base = NULL;
				}
				break;
			}
		}
		else {
			printf("Ошибка открытия файла %s.\n", authorAdress);
		}
	}
	return base;
}
//Работает

BASE *getBase() {
	BASE *base = NULL;
	char choise;
	FILE *file;
	do {
		system("cls");
		puts("Нажмите клавишу с соответствующим номером пункта:");
		puts("(1) - Создать базу вручную.");
		puts("(2) - Создать базу на основе файла.");
		choise = _getch();
		switch (choise) {
		case '1': {
			base = getBaseFromKeyboard();
			break;
		}
		case '2': {
			do {
				system("cls");
				puts("Введите путь к файлу, на основе которого создавать базу.");
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
		puts("Ввести базу не удалось.");
	}
	return base;
}
//Работает

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