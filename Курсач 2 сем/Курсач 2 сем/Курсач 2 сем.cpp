#include "stdafx.h"
#include "TRACK functions.h"
#pragma warning (disable: 4996)

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	char choise1, choise2;
	BASE *base = NULL;
	TRACK *playlist = NULL;
	bool chB = false;
	do {
		system("cls");
		puts("Нажмите клавишу с соответствующим номером пункта:");
		puts("(1) - Работа с базой песен.");
		puts("(2) - Работа с текущим плейлистом.");
		puts("(3) - Справка о программе.");
		puts("Для выхода из программы нажмите 0.");
		choise1 = _getch();
		switch (choise1)
		{
		case '1': {
			do {
				system("cls");
				puts("Нажмите клавишу с соответствующим номером пункта:");
				puts("(1) - Создать новую базу.");
				puts("(2) - Изменить/посмотреть существующую базу.");
				puts("(3) - Удалить базу.");
				choise2 = _getch();
				switch (choise2) {
				case '1': {
					base = getBase(base, &chB);
					break;
				}
				case '2': {
					base = changeBase(base, &chB);;
					break;
				}
				case '3': {
					base = deleteBase(base, &chB);
					break;
				}
				default:{
					system("cls");
					puts("Пункта с таким номером нет!");
					system("pause");
					break;
				}
				}
			} while ((choise2 < 49) || (choise2 > 51));
			break;
		}
		case '2': {
			do {
				if (chB == true & playlist != NULL) {
					chB = false;
					playlist = deletePlaylist(playlist);
					puts("Обнаружено удаление песен из базы. Плейлист был очищен.");
					system("pause");
				}
				system("cls");
				puts("Нажмите клавишу с соответствующим номером пункта:");
				puts("(1) - Создать новый плейлист.");
				puts("(2) - Вывести плейлист на экран.");
				puts("(3) - Редактировать текущий плейлист.");
				puts("(4) - Удалить текущий плейлист.");
				choise2 = _getch();
				switch (choise2) {
				case '1': {
					playlist = setPlaylist(playlist, base);
					break;
				}
				case '2': {
					printPlaylist(playlist);
					break;
				}
				case '3': {
					playlist = changePlaylist(playlist);
					break;
				}
				case '4': {
					playlist = deletePlaylist(playlist);
					break;
				}
				default: {
					system("cls");
					puts("Пункта с таким номером нет!");
					system("pause");
					break;
				}
				}
			} while ((choise2 < 49) || (choise2 > 52));
			break;
		}
		case '3': {
			FAQ();
			break;
		}
		case '0': {
			if (base != NULL) {
				base = deleteBase(base, &chB);
			}
			puts("Выход из программы...");
			break;
		}
		default: {
			system("cls");
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
		system("pause");
	} while (choise1 != '0');
	return 0;
}