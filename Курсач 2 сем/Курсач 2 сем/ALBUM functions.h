#include "SONG functions.h"
#pragma warning (disable: 4996)

ALBUM *getAlbumFromKeyboard(){
	ALBUM *album = (ALBUM*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("Введите название альбома: ");
	album->name = getStr();
	system("cls");
	printf("Введите год издания: ");
	album->year = getUnsigned();
	do{
		system("cls");
		printf("Введите количество песен в альбоме: ");
		album->songKol = getUnsigned();
		album->songs = (SONG**)realloc(album->songs, album->songKol*sizeof(SONG*));
		if (album->songs == NULL){
			do {
				system("cls");
				puts("Ошибка выделения памяти! Ввести другое количество песен?");
				puts("(1) - Да.");
				puts("(2) - Нет.");
				choise = _getch();
				switch (choise){
				case '1': {
					break;
				}
				case '2': {
					return NULL;
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
	} while (album->songs == NULL && choise == '1');
	if (album->songs != NULL){
		for (unsigned i = 0; i < album->songKol; i++){
			album->songs[i] = getSongFromKeyboard();
		}
	}
	return album;
}

ALBUM *getAlbumFromFile(FILE *albumFile){
	ALBUM *album = (ALBUM*)calloc(1, sizeof(ALBUM));
	album->name = getStrFromFile(albumFile);
	album->year = strToUnsigned(getStrFromFile(albumFile));
	album->songKol = strToUnsigned(getStrFromFile(albumFile));
	album->songs = (SONG**)realloc(album->songs, album->songKol*sizeof(SONG*));
	if (album->songs != NULL){
		for (unsigned i = 0; i < album->songKol; i++){
			album->songs[i] = getSongFromKeyboard();
		}
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
		return NULL;
	}
	return album;
}

ALBUM *getAlbum(){
	ALBUM *album = (ALBUM*)calloc(1, sizeof(ALBUM));
	char choise, choise2;
	FILE *file = NULL;
	do {
		system("cls");
		puts("Каким образов ввести альбом?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с песней: ");
				file = fopen(getStr(), "r");
				if (fileNull()) {
					
				}
				else {
					album = getAlbumFromFile(file);
				}
			} while (file == NULL && choise2 == '1');
		}
		default:
			break;
		}
	} while (choise < 49 || choise > 50);
	return album;
}

ALBUM *deleteAlbum(ALBUM *album) {
	free(album->name);
	for (unsigned i = 0; i < album->songKol; i++) {
		album->songs[i] = deleteSong(album->songs[i]);
	}
	free(album->songs);
	free(album);
	return NULL;
}

void addSongToAlbum(ALBUM *album) {
	SONG *song = NULL;
	FILE *songFile = NULL;
	char choise1, choise2;
	do {
		system("cls");
		puts("Каким образом добавить песню в альбом?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise1 = _getch();
		switch (choise1) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с песней: ");
				songFile = fopen(getStr(), "r");
				if (songFile == NULL) {
					do {
						system("cls");
						puts("Ошибка открытия файла! Ввести другой адрес?");
						puts("(1) - Да.");
						puts("(2) - Нет.");
						choise2 = _getch();
						switch (choise2)
						{
						case '1': {
							break;
						}
						case '2': {
							break;
						}
						default: {
							system("cls");
							puts("Пункта с таким номером нет!");
							system("pause");
							break;
						}
						}
					} while (choise2 < 49 || choise2 > 50);
				}
				else {
					song = getSongFromFile(songFile);
				}
			} while (songFile == NULL && choise2 == '1');
			}
		case '2': {
			song = getSongFromKeyboard();
		}
		default: {
			system("cls");
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise1 < 49 || choise1 > 50);
	if (song != NULL) {
		album->songKol++;
		album->songs = (SONG**)realloc(album->songs, album->songKol * sizeof(SONG*));
		album->songs[album->songKol - 1] = song;
		printf("Песня %s успешно добавлена в альбом %s.\n", song->name, album->name);
	}
}

void printAlbum(ALBUM *album) {
	system("cls");
	printf("Песни в альбоме %s:\n");
	for (unsigned i = 0; i < album->songKol; i++) {
		printf("%d - %s\n", i + 1, album->songs[i]->name);
	}
}

void printAlbumInfo(ALBUM *album) {
	system("cls");
	printf("Название альбома: %s\n", album->name);
	printf("Исполнитель:      %s\n", album->author->name);
	printf("Год издания:      %d\n", album->year);
	printf("Количество песен: $d\n", album->songKol);
	system("pause");
}

ALBUM *deleteSongFromAlbum(ALBUM *album) {
	unsigned num = 0;
	char choise;
	do {
		system("cls");
		printAlbum(album);
		puts("Введите номер песни, которую хотите удалить: ");
		num = getUnsigned();
		if (num > 0 && num <= album->songKol) {
			if (album->songKol == 1) {
				album = deleteAlbum(album);
			}
			else {
				album->songKol--;
				album->songs[num - 1] = deleteSong(album->songs[num - 1]);
				for (unsigned i = num - 1; i < album->songKol; i++) {
					album->songs[i] = album->songs[i + 1];
				}
				album->songs = (SONG**)realloc(album->songs, album->songKol * sizeof(SONG*));
			}
			break;
		}
		else {
			do {
				system("cls");
				puts("Песни с таким номером нет. Ввести другой номер?");
				puts("(1) - Да.");
				puts("(2) - Нет.");
				choise = _getch();
				switch (choise) {
				case '1': {
					num = 0;
					break;
				}
				case '2': {
					num = 1;
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
	} while (num == 0);
	return album;
}