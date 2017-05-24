#include "ALBUM functions.h"
#pragma warning (disable: 4996)

AUTHOR *getAuthorFromFile(FILE *file){
	system("cls");
	FILE *albumFile = NULL;
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(AUTHOR));
	if (author != NULL) {
		author->name = getStrFromFile(file);

	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return author;
}