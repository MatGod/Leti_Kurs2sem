#include "simple functions.h"
#include "structs.h"
#pragma warning (disable: 4996)

SONG *getSongFromFile(FILE *file)
{
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	char *str;
	char ch;
	unsigned i = 0;
	while ((ch = getc(file)) != '\n' && ch != EOF) {
		song->name = (char*)realloc(song->name, (i + 1) * sizeof(char));
		song->name[i] = ch;
		i++;
	}
	song->name[i] = '\0';
	i = 0;
	if (ch != EOF){
		do{
			str = getStrFromFile(file);
			if (str[0] != '\0'){
				i++;
				song->text = (char**)realloc(song->text, i*sizeof(char*));
				song->text[i - 1] = str;
			}
		} while (str[0] != '\0');
	}
	printf("����� %s ������� �������.", song->name);
	return song;
}

SONG *getSongFromKeyboard(){
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	char *str;
	unsigned kol = 0;
	printf("������� �������� �����: ");
	song->name = getStr();
	printf("������� ����� �����: (��� ��������� ����� ������ ������� ������ ������)\n");
	do{
		str = getStr();
		if (str[0] != '\0'){
			kol++;
			song->text = (char**)realloc(song->text, kol*sizeof(char*));
			song->text[kol - 1] = str;
		}
	} while (str[0] != '\0');
	return song;
}

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

void printSong(SONG *song) {
	system("cls");
	printf("�������� �����: %s\n", song->name);
	printf("�����������:	%s\n", song->author->name);
	printf("������:			%s\n\n", song->album->name);
	for (unsigned i = 0; song->text[i][0] != '\0'; i++) {
		printf("%s\n", song->text[i]);
	}
	printf("\n");
	system("pause");
}