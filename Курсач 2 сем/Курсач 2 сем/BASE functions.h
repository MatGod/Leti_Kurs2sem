#include "AUTHOR functions.h"

AUTHOR **getBaseFromKeyboard(AUTHOR **base) {
	return base;
}

AUTHOR **getBaseFromFile(FILE *file) {
	AUTHOR **base = NULL;
	return base;
}

AUTHOR **getBase(AUTHOR **base) {
	char choise;
	FILE *file;
	system("cls");
	puts("Нажмите клавишу с соответствующим номером пункта:");
	puts("(1) - Создать базу вручную.");
	puts("(2) - Создать базу на основе файла.");
	choise = _getch();
	do {
		switch (choise) {
		case '1': {
			base = getBaseFromKeyboard(base);
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
				file = NULL;
			}
			break;
		}
		}
	} while ((choise < 49) || (choise > 50));
	return base;
}

AUTHOR **deleteSongFromBase(AUTHOR **base) {
	return base;
}

AUTHOR **deleteBase(AUTHOR **base) {
	return base;
}

AUTHOR **addSongToBase(AUTHOR **base) {
	return base;
}