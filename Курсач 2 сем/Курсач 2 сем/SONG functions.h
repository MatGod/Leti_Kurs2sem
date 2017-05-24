#include "simple functions.h"
#include "structs.h"
#pragma warning (disable: 4996)

SONG *getSongFromFile(FILE *file)
{
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	if (song != NULL) {
		char *str;
		song->name = getStrFromFile(file);
		unsigned i = 0;
		do {
			song->text = (char**)realloc(song->text, (i + 1) * sizeof(char*));
			song->text[i] = getStrFromFile(file);
			i++;
		} while (song->text[i - 1][0] != '\0');
		printf("����� %s ������� �������.\n", song->name);
	}
	else {
		puts("������. ������������ ������.");
	}
	return song;
}
//��������

SONG *getSongFromKeyboard(){
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	if (song != NULL) {
		system("cls");
		char *str;
		unsigned kol = 0;
		printf("������� �������� �����: ");
		song->name = getStr();
		system("cls");
		printf("������� ����� �����: (��� ��������� ����� ������ ������� ������ ������)\n");
		do {
			str = getStr();
			puts("");
			kol++;
			song->text = (char**)realloc(song->text, kol * sizeof(char*));
			song->text[kol - 1] = str;
		} while (str[0] != '\0');
	}
	else {
		puts("������. ������������ ������.");
	}
	return song;
}
//��������

SONG *deleteSong(SONG *song){
	unsigned i;
	free(song->name);
	for (i = 0; song->text[i][0] != '\0'; i++){
		free(song->text[i]);
	}
	free(song->text[i]);
	free(song);
	return NULL;
}
//��������

void printSong(SONG *song) {
	system("cls");
	printf("�������� �����: %s\n", song->name);
	printf("�����������:	%s\n", song->author->name);
	printf("������:         %s\n", song->album->name);
	printf("���:            %s\n\n", song->album->year);
	for (unsigned i = 0; song->text[i][0] != '\0'; i++) {
		printf("%s\n", song->text[i]);
	}
	printf("\n");
	system("pause");
}
//��������