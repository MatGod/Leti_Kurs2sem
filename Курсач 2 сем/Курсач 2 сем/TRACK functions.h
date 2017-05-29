#include "BASE functions.h"

unsigned getPlaylistSize(TRACK *playlist) {
	if (playlist != NULL) {
		TRACK *track = playlist;
		unsigned i = 1;
		do {
			track = track->next;
			i++;
		} while (track->next != playlist);
		return i;
	}
	else {
		return 0;
	}
}

unsigned *randomMas(unsigned size) {
	unsigned *mas = (unsigned*)calloc(size, sizeof(unsigned));
	if (mas != NULL) {
		for (unsigned i = 0; i < size; i++) {
			mas[i] = rand() % size;
		}
	}
	else {
		puts("������. ������������ ������.");
	}
	return mas;
}

void shufflePlaylist(TRACK *playlist) {
	unsigned size = getPlaylistSize(playlist);
	unsigned *mas = randomMas(size);
	TRACK *track = playlist;
	TRACK *newTrack;
	SONG *song;
	if (mas != NULL) {
		for (unsigned i = 0; i < size; i++) {
			newTrack = playlist;
			for (unsigned j = 1; j <= mas[i]; j++) {
				newTrack = newTrack->next;
			}
			song = track->song;
			track->song = newTrack->song;
			newTrack->song = song;
			track = track->next;
		}
	}
}

TRACK *deleteTrack(TRACK *playlist, TRACK *track) {
	if ((playlist != NULL) && (track != NULL)) {
		if (track == playlist) {
			if (playlist->next != playlist) {
				playlist = playlist->next;
			}
			else {
				free(playlist);
				return NULL;
			}
		}
		track->next->prev = track->prev;
		track->prev->next = track->next;
		free(track);
	}
	return playlist;
}
//��������

TRACK *deletePlaylist(TRACK *playlist) {
	TRACK *track = playlist->next;
	playlist->prev->next = NULL;
	while (playlist != NULL) {
		free(playlist);
		playlist = track;
		if (track != NULL) {
			track = track->next;
		}
	}
	return NULL;
}
//��������

void printPlaylist(TRACK *playlist) {
	system("cls");
	if (playlist == NULL) {
		puts("�������� ����.");
	}
	else {
		TRACK *track = playlist;
		unsigned i = 1;
		do {
			printf("%d)%s - %s\n", i, track->song->author->name, track->song->name);
			track = track->next;
			i++;
		} while (track != playlist);
	}
}
//��������

AUTHOR *chooseAuthorFromBase(BASE *base) {
	unsigned num;
	AUTHOR *author = base->authors;
	do {
		printBase(base);
		puts("������� ����� �����������.");
		num = strToUnsigned(getStr());
		if (num > 0) {
			for (unsigned i = 1; i < num && author != NULL; i++) {
				author = author->next;
			}
		}
		if (num == 0 || author == NULL) {
			num = notAuthorInBase();
		}
		else {
			return author;
		}
	} while (num == 0);
	return NULL;
}
//��������

ALBUM *chooseAlbumFromAuthor(AUTHOR *author) {
	unsigned num;
	do {
		system("cls");
		printAuthor(author);
		puts("������� ����� �������.");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			return author->albums[num - 1];
		}
		else {
			num = notAlbumInAuthor();
		}
	} while (num == 0);
	return NULL;
}
//��������

SONG *chooseSongFromAlbum(ALBUM *album) {
	unsigned num = 0;
	do {
		system("cls");
		printAlbum(album);
		puts("������� ����� �����.");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= album->songKol) {
			return album->songs[num - 1];
		}
		else {
			num = notSongInAlbum();
		}
	} while (num == 0);
	return NULL;
}
//��������

unsigned notTrackInPlaylist() {
	char choise;
	do {
		system("cls");
		puts("����� � ����� ������� ���. ������ ������ �����?");
		puts("(1) - ��.");
		puts("(2) - ���.");
		choise = _getch();
		switch (choise) {
		case '1': {
			return 0;
			break;
		}
		case '2': {
			return 1;
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 50);
}
//��������

char *getTrackCharPole(TRACK *track, char mode) {
	switch (mode) {
	case 's': {
		return track->song->author->name;
	}
	case 'a': {
		return track->song->album->name;
	}
	}
}
//��������

TRACK *chooseTrackFromPlaylist(TRACK *playlist) {
	unsigned num, i;
	do {
		printPlaylist(playlist);
		TRACK *track = playlist;
		puts("������� ����� �����.");
		num = strToUnsigned(getStr());
		if (num > 0) {
			i = 1;
			if (num > 1) {
				do {
					track = track->next;
					i++;
				} while (i != num && track->next != playlist);
			}
		}
		if (i != num) {
			num = notTrackInPlaylist();
		}
		else {
			return track;
		}
	} while (num == 0);
	return NULL;
}
//��������

TRACK *addSongToPlaylist(TRACK *playlist, SONG *song) {
	if (song != NULL) {
		if (playlist == NULL) {
			playlist = (TRACK*)calloc(1, sizeof(TRACK));
			if (playlist != NULL) {
				playlist->song = song;
				playlist->next = playlist;
				playlist->prev = playlist;
			}
		}
		else {
			TRACK *track = (TRACK*)calloc(1, sizeof(TRACK));
			if (track != NULL) {
				track->song = song;
				track->next = playlist;
				playlist->prev->next = track;
				track->prev = playlist->prev;
				playlist->prev = track;
			}
		}
	}
	return playlist;
}
//��������

TRACK *addAlbumToPlaylist(TRACK *playlist, ALBUM *album) {
	if (album != NULL) {
		for (unsigned i = 0; i < album->songKol; i++) {
			playlist = addSongToPlaylist(playlist, album->songs[i]);
		}
	}
	return playlist;
}
//��������

TRACK *addAuthorToPlaylist(TRACK *playlist, AUTHOR *author) {
	if (author != NULL) {
		for (unsigned i = 0; i < author->albKol; i++) {
			playlist = addAlbumToPlaylist(playlist, author->albums[i]);
		}
	}
	return playlist;
}
//��������

TRACK *allBaseToPlaylist(TRACK *playlist, BASE *base) {
	AUTHOR *author = base->authors;
	while (author != NULL) {
		playlist = addAuthorToPlaylist(playlist, author);
		author = author->next;
	}
	return playlist;
}
//��������

TRACK *setPlaylist(TRACK *playlist, BASE *base) {
	if (playlist != NULL) {
		playlist = deletePlaylist(playlist);
	}
	if (base == NULL) {
		puts("���� �����. ������� �������� �� �������.");
	}
	else {
		char choise;
		do {
			system("cls");
			puts("������� ������� � ��������������� ������� ������.");
			puts("(1) - ������ ��� ���� � ��������.");
			puts("(2) - ������ ����������� ������.");
			puts("(3) - ������ ���������� ������.");
			puts("(4) - ������ ���������� �����.");
			choise = _getch();
			switch (choise) {
			case '1': {
				playlist = allBaseToPlaylist(playlist, base);
				break;
			}
			case '2': {
				playlist = addAuthorToPlaylist(playlist, chooseAuthorFromBase(base));
				break;
			}
			case '3': {
				playlist = addAlbumToPlaylist(playlist, chooseAlbumFromAuthor(chooseAuthorFromBase(base)));
				break;
			}
			case '4': {
				playlist = addSongToPlaylist(playlist, chooseSongFromAlbum(chooseAlbumFromAuthor(chooseAuthorFromBase(base))));
				break;
			}
			default:
				system("cls");
				puts("������ � ����� ������� ���!");
				system("pause");
				break;
			}
		} while (choise < 49 || choise > 52);
	}
	if (playlist != NULL) {
		puts("�������� ������.");
	}
	else {
		puts("�������� �� ������.");
	}
	return playlist;
}
//��������

TRACK *deleteTracksByPole(TRACK *playlist) {
	system("cls");
	if (playlist == NULL) {
		puts("�������� ����.");
	}
	else {
		char choise, mode;
		char *name;
		do {
			system("cls");
			puts("������� ������� � ��������������� ������� ������.");
			puts("(1) - ������� ����� ������������ �����������.");
			puts("(2) - ������� ����� �� ������������ �������.");
			choise = _getch();
			system("cls");
			switch (choise) {
			case '1': {
				mode = 's';
				puts("������� �����������:");
				break;
			}
			case '2': {
				mode = 'a';
				puts("������� �������� �������:");
				break;
			}
			default: {
				puts("������ � ����� ������� ���!");
				system("pause");
				break;
			}
			}
		} while (choise < 49 || choise > 50);
		name = getStr();
		TRACK *track = playlist;
		do {
			if (equalStrs(name, getTrackCharPole(track, mode))) {
				track = track->next;
				playlist = deleteTrack(playlist, track->prev);
			}
			else {
				track = track->next;
			}
		} while (track->next != playlist);
		if (equalStrs(name, getTrackCharPole(playlist->prev, mode))) {
			playlist = deleteTrack(playlist, playlist->prev);
		}
	}
	return playlist;
}
//��������

TRACK *deleteTracksFromPlaylist(TRACK *playlist) {
	system("cls");
	if (playlist == NULL) {
		puts("�������� ����.");
	}
	else {
		char choise;
		do {
			system("cls");
			puts("������� ������� � ��������������� ������� ������.");
			puts("(1) - ������� ����������� ����.");
			puts("(2) - ������� ��������� ������ �� ������/�������.");
			choise = _getch();
			system("cls");
			switch (choise) {
			case '1': {
				playlist = deleteTrack(playlist, chooseTrackFromPlaylist(playlist));
				break;
			}
			case '2': {
				playlist = deleteTracksByPole(playlist);
				break;
			}
			default: {
				puts("������ � ����� ������� ���!");
				system("pause");
				break;
			}
			}
		} while (choise < 49 || choise > 50);
	}
	return playlist;
}
//��������

bool compareTracks(TRACK *track1, TRACK *track2, char mode) {
	switch (mode)
	{
	case 'n': {
		return compareStrs(track1->song->name, track2->song->name);
	}
	case 's': {
		return compareStrs(track1->song->author->name, track2->song->author->name);
	}
	case 'a': {
		return compareStrs(track1->song->album->name, track2->song->album->name);
	}
	case 'y': {
		if (track1->song->album->year <= track2->song->album->year) {
			return false;
		}
		else {
			return true;
		}
	}
	}
}
//��������

void sortPlaylist(TRACK *playlist) {
	char choise, mode;
	do {
		system("cls");
		puts("������� ������� � ��������������� ������� ������.");
		puts("(1) - ������������� �������� �� �������� �����.");
		puts("(2) - ������������� �������� �� �����������.");
		puts("(3) - ������������� �������� �� �������� �������.");
		puts("(4) - ������������� �������� �� ����.");
		choise = _getch();
		switch (choise) {
		case '1': {
			mode = 'n';
			break;
		}
		case '2': {
			mode = 's';
			break;
		}
		case '3': {
			mode = 'a';
			break;
		}
		case '4': {
			mode = 'y';
			break;
		}
		default:
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
	} while (choise < 49 || choise > 52);
	TRACK *track;
	SONG *song;
	bool pom;
	do {
		pom = false;
		track = playlist;
		do {
			if (compareTracks(track, track->next, mode)) {
				song = track->song;
				track->song = track->next->song;
				track->next->song = song;
				pom = true;
			}
			track = track->next;
		} while (track->next != playlist);
	} while (pom == true);
}
//��������

TRACK *changePlaylist(TRACK *playlist) {
	system("cls");
	if (playlist == NULL) {
		puts("�������� ����.");
	}
	else {
		char choise;
		do {
			system("cls");
			puts("������� ������� � ��������������� ������� ������.");
			puts("(1) - ������������� ��������.");
			puts("(2) - ���������� ��������.");
			puts("(3) - ������� ����� �� ���������.");
			choise = _getch();
			switch (choise) {
			case '1': {
				sortPlaylist(playlist);
				break;
			}
			case '2': {
				shufflePlaylist(playlist);
				break;
			}
			case '3': {
				playlist = deleteTracksFromPlaylist(playlist);
				break;
			}
			default:
				system("cls");
				puts("������ � ����� ������� ���!");
				system("pause");
				break;
			}
		} while (choise < 49 || choise > 51);
	}
	return playlist;
}
