#include "simple functions.h"
#include "structs.h"
#pragma warning (disable: 4996)

SONG *getSongFromFile(FILE *file)
{
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	if (song != NULL) {
		char **test;
		song->name = getStrFromFile(file);
		unsigned i = 0;
		do {
			test = (char**)realloc(song->text, (i + 1) * sizeof(char*));
			if (test != NULL) {
				song->text = test;
				song->text[i] = getStrFromFile(file);
				i++;
			}
			else {
				song->text[i - 1] = "\0";
				break;
			}
		} while (song->text[i - 1][0] != '\0');
		printf("Песня %s считана.\n", song->name);
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return song;
}
//Работает

SONG *getSongFromKeyboard(){
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	if (song != NULL) {
		system("cls");
		char *str;
		char **test;
		unsigned kol = 0;
		printf("Введите название песни: ");
		song->name = getStr();
		system("cls");
		printf("Введите текст песни: (Для окончания ввода текста введите пустую строку)\n");
		do {
			str = getStr();
			puts("");
			kol++;
			test = (char**)realloc(song->text, kol * sizeof(char*));
			if (test != NULL) {
				song->text = test;
				song->text[kol - 1] = str;
			}
			else {
				song->text[kol - 1] = "\0";
				break;
			}
		} while (str[0] != '\0');
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return song;
}
//Работает

SONG *deleteSong(SONG *song, bool *chB){
	unsigned i;
	*chB = true;
	free(song->name);
	for (i = 0; song->text[i][0] != '\0'; i++){
		free(song->text[i]);
	}
	free(song->text[i]);
	free(song);
	return NULL;
}
//Работает

void printSong(SONG *song) {
	system("cls");
	printf("Название песни: %s\n", song->name);
	printf("Исполнитель:	%s\n", song->author->name);
	printf("Альбом:         %s\n", song->album->name);
	printf("Год:            %d\n\n", song->album->year);
	for (unsigned i = 0; song->text[i][0] != '\0'; i++) {
		printf("%s\n", song->text[i]);
	}
	printf("\n");
	system("pause");
}
//Работает