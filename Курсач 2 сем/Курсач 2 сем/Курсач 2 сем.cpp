#include "stdafx.h"
#include "TRACK functions.h"
#pragma warning (disable: 4996)

/*int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	char choise1, choise2;
	char ch;
	AUTHOR **base = NULL;
	unsigned authors = 0;
	TRACK *playlist = NULL;
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
			system("cls");
			puts("Нажмите клавишу с соответствующим номером пункта:");
			puts("(1) - Создать новую базу.");
			puts("(2) - Изменить/посмотреть существующую базу.");
			puts("(3) - Удалить базу.");
			choise2 = _getch();
			do {
				switch (choise2) {
				case '1': {
					base = getBase(base);
					break;
				}
				case '2': {
					base = сhangeBase(base);
					break;
				}
				case '3': {
					base = deleteBase(base);
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
		case '2': { // работа с плейлистом
			system("cls");
			puts("Нажмите клавишу с соответствующим номером пункта:");
			puts("(1) - Создать новый плейлист.");
			puts("(2) - Редактировать/посмотреть текущий плейлист.");
			puts("(3) - Удалить текущий плейлист.");
			choise2 = _getch();
			do {
				switch (choise2) {
				case '1': {
					playlist = setPlaylist(playlist);
					break;
				}
				case '2': {
					playlist = changePlaylist(playlist);
					break;
				}
				case '3': {
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
			} while ((choise2 < 49) || (choise2 > 51));
			break;
		}
		case '3': {
			FAQ();
			break;
		}
		case '0': {
			break;
		}
		default: {
			system("cls");
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise1 != '0');
	puts("Выход из программы...");
	_getch();
	return 0;
}
*/

int _tmain(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "Russian");
	BASE *base = getBase();
	printSong(base->authors->albums[0]->songs[0]);
	system("pause");
	return 0;
}