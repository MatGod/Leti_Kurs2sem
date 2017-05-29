#include "SONG functions.h"
#pragma warning (disable: 4996)

ALBUM *deleteAlbum(ALBUM *album, bool *chB) {
	free(album->name);
	for (unsigned i = 0; i < album->songKol; i++) {
		album->songs[i] = deleteSong(album->songs[i], chB);
	}
	free(album->songs);
	free(album);
	return NULL;
}
//Работает

ALBUM *getAlbumFromKeyboard(){
	bool a;
	ALBUM *album = (ALBUM*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("Введите название альбома: ");
	album->name = getStr();
	system("cls");
	printf("Введите год издания: ");
	album->year = strToUnsigned(getStr());
	do{
		system("cls");
		printf("Введите количество песен в альбоме: ");
		album->songKol = strToUnsigned(getStr());
		album->songs = (SONG**)calloc(album->songKol, sizeof(SONG*));
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
					album->songKol = 0;
					album = deleteAlbum(album, &a);
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
			if (album->songs[i] != NULL) {
				album->songs[i]->album = album;
			}
			else {
				album->songKol = i;
				album->songs = (SONG**)realloc(album->songs, album->songKol*sizeof(SONG*));
				if (i == 0) {
					album = deleteAlbum(album, &a);
				}
				break;
			}
		}
	}
	else {
		album->songKol = 0;
		album = deleteAlbum(album, &a);
	}
	return album;
}
//Работает

ALBUM *getAlbumFromFile(FILE *albumFile){
	system("cls");
	bool a;
	ALBUM *album = (ALBUM*)calloc(1, sizeof(ALBUM));
	if (album != NULL) {
		char *songAdress;
		FILE *songFile;
		SONG *song;
		unsigned i = 0;
		album->name = getStrFromFile(albumFile);
		album->year = strToUnsigned(getStrFromFile(albumFile));
		do {
			songAdress = getStrFromFile(albumFile);
			if (songAdress[0] != '\0') {
				songFile = fopen(songAdress, "r");
				if (songFile == NULL) {
					printf("Ошибка открытия файла\n%s.\n", songAdress);
				}
				else {
					song = getSongFromFile(songFile);
					if (song != NULL) {
						album->songs = (SONG**)realloc(album->songs, (i + 1) * sizeof(SONG*));
						album->songs[i] = song;
						album->songs[i]->album = album;
						i++;
					}
					fclose(songFile);
				}
			}
		} while (songAdress[0] != '\0');
		album->songKol = i;
		if (i == 0) {
			puts("Ни одной песни не введено. Альбом не создан.");
			album = deleteAlbum(album, &a);
			return NULL;
		}
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return album;
}
//Работает

ALBUM *getAlbum(){
	ALBUM *album = NULL;
	char choise;
	FILE *file = NULL;
	do {
		system("cls");
		puts("Каким образом ввести альбом?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с альбомом: ");
				file = fopen(getStr(), "r");
				if (file == NULL) {
					if (!fileNull()) {
						break;
					}
				}
				else {
					album = getAlbumFromFile(file);
					fclose(file);
				}
			} while (file == NULL);
			break;
		}
		case '2':{
			album = getAlbumFromKeyboard();
			break;
		}
		default:
			break;
		}
	} while (choise < 49 || choise > 50);
	if (album == NULL) {
		puts("Добавить альбом не удалось.");
	}
	else {
		puts("Альбом добавлен в базу.");
	}
	return album;
}
//Работает

void addSongToAlbum(ALBUM *album) {
	bool a;
	SONG *song = NULL;
	FILE *songFile = NULL;
	char choise;
	do {
		system("cls");
		puts("Каким образом добавить песню в альбом?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с песней: ");
				songFile = fopen(getStr(), "r");
				if (songFile == NULL) {
					if (!fileNull()) {
						break;
					}
				}
				else {
					song = getSongFromFile(songFile);
				}
			} while (songFile == NULL);
			break;
			}
		case '2': {
			song = getSongFromKeyboard();
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
	if (song != NULL) {
		SONG **test = (SONG**)realloc(album->songs, (album->songKol + 1) * sizeof(SONG*));
		if (test != NULL) {
			album->songKol++;
			album->songs = test;
			album->songs[album->songKol - 1] = song;
			song->album = album;
			song->author = album->author;
			printf("Песня %s успешно добавлена в альбом %s.\n", song->name, album->name);
		}
		else {
			puts("Ошибка. Недостаточно памяти.");
			song = deleteSong(song, &a);
		}
	}
}
//Работает

void printAlbum(ALBUM *album) {
	system("cls");
	if (album != NULL) {
		printf("Песни в альбоме %s:\n", album->name);
		for (unsigned i = 0; i < album->songKol; i++) {
			printf("%d - %s\n", i + 1, album->songs[i]->name);
		}
	}
	else {
		puts("Альбома не существует.");
	}
}
//Работает

void printAlbumInfo(ALBUM *album) {
	system("cls");
	printf("Название альбома: %s\n", album->name);
	printf("Исполнитель:      %s\n", album->author->name);
	printf("Год издания:      %d\n", album->year);
	printf("Количество песен: %d\n", album->songKol);
	system("pause");
}
//Работает

unsigned notSongInAlbum() {
	char choise;
	do {
		system("cls");
		puts("Песни с таким номером нет. Ввести другой номер?");
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

void printSongFromAlbum(ALBUM *album) {
	unsigned num = 0;
	do {
		system("cls");
		printAlbum(album);
		puts("Введите номер песни, которую хотите вывести на экран: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= album->songKol) {
			printSong(album->songs[num - 1]);
			break;
		}
		else {
			num = notSongInAlbum();
		}
	} while (num == 0);
}
//Работает

ALBUM *deleteSongFromAlbum(ALBUM *album, bool *chB) {
	unsigned num = 0;
	do {
		system("cls");
		printAlbum(album);
		puts("Введите номер песни, которую хотите удалить: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= album->songKol) {
			if (album->songKol == 1) {
				album = deleteAlbum(album, chB);
			}
			else {
				album->songKol--;
				album->songs[num - 1] = deleteSong(album->songs[num - 1], chB);
				for (unsigned i = num - 1; i < album->songKol; i++) {
					album->songs[i] = album->songs[i + 1];
				}
				album->songs = (SONG**)realloc(album->songs, album->songKol * sizeof(SONG*));
			}
			break;
		}
		else {
			num = notSongInAlbum();
		}
	} while (num == 0);
	return album;
}
//Работает

ALBUM *changeAlbum(ALBUM *album, bool *chB) {
	char choise;
	do {
		system("cls");
		puts("Что вы хотите сделать с альбомом?");
		puts("(1) - Показать информацию о альбоме.");
		puts("(2) - Показать список песен.");
		puts("(3) - Вывести на экран одну из песен.");
		puts("(4) - Добавить песни в альбом.");
		puts("(5) - Удалить песню из альбома.");
		puts("(6) - Удалить альбом.");
		choise = _getch();
		switch (choise)
		{
		case '1': {
			printAlbumInfo(album);
			break;
		}
		case '2': {
			printAlbum(album);
			break;
		}
		case '3': {
			printSongFromAlbum(album);
			break;
		}
		case '4': {
			addSongToAlbum(album);
			break;
		}
		case '5': {
			album = deleteSongFromAlbum(album, chB);
			break;
		}
		case '6': {
			album = deleteAlbum(album, chB);
			break;
		}
		default: {
			system("cls");
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 54);
	return album;
}
//Работает

void fixSongAuthor(ALBUM *album) {
	for (unsigned i = 0; i < album->songKol; i++) {
		album->songs[i]->author = album->author;
	}
}
//Работает