#include "ALBUM functions.h"
#pragma warning (disable: 4996)

AUTHOR *getAuthorFromFile(FILE *file){
	system("cls");
	FILE *albumFile = NULL;
	char *albumAdress;
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(AUTHOR));
	if (author != NULL) {
		author->name = getStrFromFile(file);
		do {
			albumAdress = getStrFromFile(file);
			if (albumAdress[0] != '\0') {

			}
		} while (albumAdress[0] != '\0');
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return author;
}