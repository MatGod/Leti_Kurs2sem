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
	return album;
}
