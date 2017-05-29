#include "ALBUM functions.h"
#pragma warning (disable: 4996)

AUTHOR *deleteAuthor(AUTHOR *author, bool *chB) {
	free(author->name);
	for (unsigned i = 0; i < author->albKol; i++) {
		author->albums[i] = deleteAlbum(author->albums[i], chB);
	}
	free(author->albums);
	free(author);
	return NULL;
}
//��������

AUTHOR *getAuthorFromFile(FILE *file){
	system("cls");
	FILE *albumFile = NULL;
	char *albumAdress;
	bool a;
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(AUTHOR));
	if (author != NULL) {
		author->name = getStrFromFile(file);
		ALBUM *album = NULL;
		unsigned i = 0;
		do {
			albumAdress = getStrFromFile(file);
			if (albumAdress[0] != '\0') {
				albumFile = fopen(albumAdress, "r");
				if (albumFile == NULL) {
					printf("������ �������� ����� %s.\n", albumAdress);
				}
				else {
					album = getAlbumFromFile(albumFile);
					if (album != NULL) {
						i++;
						author->albums = (ALBUM**)realloc(author->albums, i * sizeof(ALBUM*));
						author->albums[i - 1] = album;
						author->albums[i - 1]->author = author;
						fixSongAuthor(author->albums[i - 1]);
					}
					fclose(albumFile);
				}
			}
		} while (albumAdress[0] != '\0');
		author->albKol = i;
		if (i == 0) {
			author = deleteAuthor(author, &a);
			puts("�� ���� ������ �� �����. ����������� �� ������.");
		}
	}
	else {
		puts("������. ������������ ������.");
	}
	return author;
}
//��������

AUTHOR *getAuthorFromKeyboard() {
	bool a;
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("������� �����������: ");
	author->name = getStr();
	do {
		system("cls");
		printf("������� ���������� ��������: ");
		author->albKol = strToUnsigned(getStr());
		if (author->albKol > 0) {
			author->albums = (ALBUM**)calloc(author->albKol, sizeof(SONG*));
			if (author->albums == NULL) {
				do {
					system("cls");
					puts("������������ ������! ������ ������ ���������� ��������?");
					puts("(1) - ��.");
					puts("(2) - ���.");
					choise = _getch();
					switch (choise) {
					case '1': {
						break;
					}
					case '2': {
						return NULL;
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
		}
		else {
			author = deleteAuthor(author, &a);
			return NULL;
		}
	} while (author->albums == NULL && choise == '1');
	if (author->albums != NULL) {
		for (unsigned i = 0; i < author->albKol; i++) {
			author->albums[i] = getAlbumFromKeyboard();
			if (author->albums[i] != NULL) {
				author->albums[i]->author = author;
				fixSongAuthor(author->albums[i]);
			}
			else {
				author->albKol = i;
				author->albums = (ALBUM**)realloc(author->albums, author->albKol*sizeof(SONG*));
				if (i == 0) {
					author = deleteAuthor(author, &a);
				}
				break;
			}
		}
	}
	else {
		author->albKol = 0;
		author = deleteAuthor(author, &a);
	}
	return author;
}
//��������

AUTHOR *getAuthor() {
	AUTHOR *author = NULL;
	char choise;
	FILE *file = NULL;
	do {
		system("cls");
		puts("����� ������� ������ �����������?");
		puts("(1) - ������� �� �����.");
		puts("(2) - ������ � ����������.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("������� ����� ����� � ������������: ");
				file = fopen(getStr(), "r");
				if (file == NULL) {
					if (!fileNull()) {
						break;
					}
				}
				else {
					author = getAuthorFromFile(file);
				}
			} while (file == NULL);
			break;
		}
		case '2': {
			author = getAuthorFromKeyboard();
			break;
		}
		default:
			break;
		}
	} while (choise < 49 || choise > 50);
	if (author == NULL) {
		puts("������� ����������� �� �������.");
	}
	else {
		puts("����������� ������� �������� � ����.");
	}
	system("pause");
	return author;
}
//��������

void addAlbumToAuthor(AUTHOR *author) {
	bool a;
	ALBUM *album = NULL;
	FILE *albumFile = NULL;
	char choise;
	do {
		system("cls");
		puts("����� ������� �������� ������ �����������?");
		puts("(1) - ������� �� �����.");
		puts("(2) - ������ � ����������.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("������� ����� ����� � ��������: ");
				albumFile = fopen(getStr(), "r");
				if (albumFile == NULL) {
					if (!fileNull()) {
						break;
					}
				}
				else {
					album = getAlbumFromFile(albumFile);
				}
			} while (albumFile == NULL);
			break;
		}
		case '2': {
			album = getAlbumFromKeyboard();
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
	if (album != NULL) {
		ALBUM **test = (ALBUM**)realloc(author->albums, (author->albKol + 1) * sizeof(ALBUM*));
		if (test != NULL) {
			author->albKol++;
			author->albums = test;
			author->albums[author->albKol - 1] = album;
			album->author = author;
			fixSongAuthor(album);
			printf("������ %s ������� �������� ����������� %s.\n", album->name, author->name);
		}
		else {
			puts("������. ������������ ������.");
			album = deleteAlbum(album, &a);
		}
	}
	else {
		puts("�������� ������ �� �������.");
	}
}
//��������

void printAuthor(AUTHOR *author) {
	system("cls");
	printf("������� ����������� %s:\n", author->name);
	for (unsigned i = 0; i < author->albKol; i++) {
		printf("%d - %s\n", i + 1, author->albums[i]->name);
	}
}
//��������

unsigned notAlbumInAuthor() {
	char choise;
	do {
		system("cls");
		puts("������� � ����� ������� ���. ������ ������ �����?");
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

AUTHOR *deleteAlbumFromAuthor(AUTHOR *author, bool *chB) {
	unsigned num = 0;
	do {
		system("cls");
		printAuthor(author);
		puts("������� ����� �������, ������� ������ �������: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			if (author->albKol == 1) {
				author = deleteAuthor(author, chB);
			}
			else {
				author->albKol--;
				author->albums[num - 1] = deleteAlbum(author->albums[num - 1], chB);
				for (unsigned i = num - 1; i < author->albKol; i++) {
					author->albums[i] = author->albums[i + 1];
				}
				author->albums = (ALBUM**)realloc(author->albums, author->albKol * sizeof(ALBUM*));
			}
			break;
		}
		else {
			num = notAlbumInAuthor();
		}
	} while (num == 0);
	return author;
}
//��������

AUTHOR *changeAlbumInAuthor(AUTHOR *author, bool *chB) {
	unsigned num;
	do {
		system("cls");
		printAuthor(author);
		puts("������� ����� �������, ������� ������ ��������: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			author->albums[num - 1] = changeAlbum(author->albums[num - 1], chB);
			if (author->albums[num - 1] == NULL) {
				author->albKol--;
				if (num == 1) {
					author = deleteAuthor(author, chB);
				}
				else{
					for (unsigned i = num - 1; i < author->albKol; i++) {
						author->albums[i] = author->albums[i + 1];
					}
					author->albums = (ALBUM**)realloc(author->albums, author->albKol * sizeof(ALBUM*));
				}
			}
			break;
		}
		else {
			num = notAlbumInAuthor();
		}
	} while (num == 0);
	return author;
}
//��������

AUTHOR *changeAuthor(AUTHOR *author, bool *chB) {
	char choise;
	do {
		system("cls");
		puts("��� �� ������ ������� � ������������?");
		puts("(1) - �������� ������ ��������.");
		puts("(2) - �������� ������ �����������.");
		puts("(3) - ����������/�������� ���� �� ��������.");
		puts("(4) - ������� ������ � �����������.");
		puts("(5) - ������� �����������.");
		choise = _getch();
		switch (choise)
		{
		case '1': {
			printAuthor(author);
			break;
		}
		case '2': {
			addAlbumToAuthor(author);
			break;
		}
		case '3': {
			author = changeAlbumInAuthor(author, chB);
			break;
		}
		case '4': {
			author = deleteAlbumFromAuthor(author, chB);
			break;
		}
		case '5': {
			author = deleteAuthor(author, chB);
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 53);
	return author;
}
//��������