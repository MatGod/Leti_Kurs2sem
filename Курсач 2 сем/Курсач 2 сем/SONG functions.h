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
	printf("Песня %s успешно считана.", song->name);
	return song;
}

SONG *getSongFromKeyboard(){
	SONG *song = (SONG*)calloc(1, sizeof(SONG));
	char *str;
	unsigned kol = 0;
	printf("Введите название песни: ");
	song->name = getStr();
	printf("Введите текст песни: (Для окончания ввода текста введите пустую строку)\n");
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