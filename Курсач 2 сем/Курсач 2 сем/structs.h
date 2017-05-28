#include "stdafx.h"

struct SONG{
	struct AUTHOR *author = NULL;
	struct ALBUM *album = NULL;
	char *name = NULL;
	char **text = NULL;
};
struct ALBUM{
	char *name = NULL;
	unsigned year = 0;
	unsigned songKol = 0;
	SONG **songs = NULL;
	struct AUTHOR *author = NULL;
};
struct AUTHOR{
	char *name = NULL;
	unsigned albKol = 0;
	ALBUM **albums = NULL;
	AUTHOR *next = NULL;
};
struct TRACK {
	SONG *song = NULL;
	TRACK *next = NULL;
	TRACK *prev = NULL;
};
struct BASE {
	AUTHOR *authors = NULL;
};