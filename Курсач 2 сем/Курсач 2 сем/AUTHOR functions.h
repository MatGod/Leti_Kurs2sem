#include "ALBUM functions.h"
#pragma warning (disable: 4996)

AUTHOR *getAuthor(){
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(AUTHOR));
	return author;
}