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
	puts("������� ������� � ��������������� ������� ������:");
	puts("(1) - ������� ���� �������.");
	puts("(2) - ������� ���� �� ������ �����.");
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