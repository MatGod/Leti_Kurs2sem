#include "BASE functions.h"

TRACK *setPlaylist(TRACK *playlist){
	return playlist;
}

TRACK *changePlaylist(TRACK *playlist){
	char choise, choise4;
	system("cls");
	puts("Нажмите клавишу с соответствующим номером пункта:");
	puts("(1) - Добавить песни.");
	puts("(2) - Удалить песни.");
	puts("(3) - Сортировать плейлист.");
	puts("(4) - Перемешать плейлист.");
	choise = _getch();
	do {
		switch (choise) {
		case '1': { // добавить
			system("cls");
			puts("Нажмите клавишу с соответствующим номером пункта:");
			puts("Добавить:");
			puts("(1) - Все песни одного исполнителя.");
			puts("(2) - Все песни из одного альбома.");
			puts("(3) - Все песни одного года выхода.");
			puts("(4) - Конкретную песню.");
			choise4 = _getch();
			do{
				switch (choise4) {
				case '1':{
					system("cls");

					break;
				}
				case '2': {

					break;
				}
				case '3': {

					break;
				}
				case '4': {

					break;
				}
				default:{
					system("cls");
					puts("Пункта с таким номером нет!");
					system("pause");
					break;
				}
				}
			} while ((choise4 < 49) || (choise4 > 52));
			break;
		}
		case '2': {
			break;
		}
		case '3': {
			break;
		}
		case '4': {
			break;
		}
		default: {
			system("cls");
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while ((choise < 49) || (choise > 52));
	system("pause");
	return playlist;
}

TRACK *deletePlaylist(TRACK *playlist){
	return playlist;
}