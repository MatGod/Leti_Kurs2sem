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
	ALBUM *next = NULL;
	struct AUTHOR *author = NULL;
};
struct AUTHOR{
	char *name = NULL;
	ALBUM *albums = NULL;
};
struct TRACK {
	SONG *song = NULL;
	TRACK *next = NULL;
	TRACK *prev = NULL;
};