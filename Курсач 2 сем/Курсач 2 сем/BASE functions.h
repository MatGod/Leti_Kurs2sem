#include "AUTHOR functions.h"

AUTHOR *getLastAuthor(BASE *base) {
	AUTHOR *author = base->authors;
	while (author->next != NULL) {
		author = author->next;
	}
	return author;
}
//Работает

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
		puts("База удалена.");
	}
	return NULL;
}
//Работает

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
			printf("Ошибка. Количество успешно введённых исполнителей - %d.\n", i - 1);
			if (i == 1) {
				base = deleteBase(base);
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
						printf("Ошибка. Не удалось ввести исполнителя из %s.\n", authorAdress);
					}
				}
				else {
					printf("Ошибка открытия файла %s.\n", authorAdress);
				}
			}
		} while (authorAdress[0] != '\0');
		if (base->authors == NULL) {
			base = deleteBase(base);
			puts("Не удалось ввести ни одного исполнителя. База не введена.");
		}
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return base;
}
//Работает

BASE *getBase(BASE *base) {
	if (base != NULL) {
		base = deleteBase(base);
	}
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
	else {
		puts("База успешно создана.");
	}
	return base;
}
//Работает

void printBase(BASE *base) {
	system("cls");
	if (base == NULL) {
		puts("База пуста.");
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
//Работает

unsigned notAuthorInBase() {
	char choise;
	do {
		system("cls");
		puts("Исполнителя с таким номером нет. Ввести другой номер?");
		puts("(1) - Да.");
		puts("(2) - Нет.");
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
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 50);
}
//Работает

BASE *deleteAuthorFromBase(BASE *base) {
	AUTHOR *author;
	AUTHOR *prevAuthor;
	unsigned num;
	do {
		printBase(base);
		author = base->authors;
		prevAuthor = NULL;
		system("cls");
		puts("Введите номер исполнителя, которого хотите удалить.");
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
		puts("Из базы удалён единственный исполнитель. База пуста.");
	}
	return base;
}
//Рабоатет

void addAuthorToBase(BASE *base) {
	AUTHOR *author = getLastAuthor(base);
	author->next = getAuthor();
}
//Работает

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
		puts("Введите номер исполнителя, которого хотите посмотреть/изменить.");
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
		puts("Из базы удалён единственный исполнитель. База пуста.");
	}
	return base;
}
//Работает

BASE *changeBase(BASE *base) {
	if (base == NULL) {
		puts("База пуста.");
	}
	else {
		char choise;
		do {
			system("cls");
			puts("Что вы хотите сделать с базой?");
			puts("(1) - Показать список исполнителей в базе");
			puts("(2) - Добавить исполнителя.");
			puts("(3) - Посмотреть/изменить одиного из исполнителей.");
			puts("(4) - Удалить исполнителя.");
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
				puts("Пункта с таким номером нет!");
				system("pause");
				break;
			}
			}
		} while (choise < 49 || choise > 52);
	}
	return base;
}
//Работает