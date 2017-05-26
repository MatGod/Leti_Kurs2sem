#include "ALBUM functions.h"
#pragma warning (disable: 4996)

AUTHOR *deleteAuthor(AUTHOR *author) {
	free(author->name);
	for (unsigned i = 0; i < author->albKol; i++) {
		author->albums[i] = deleteAlbum(author->albums[i]);
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
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(AUTHOR));
	if (author != NULL) {
		author->name = getStrFromFile(file);
		author->albKol = strToUnsigned(getStrFromFile(file));
		ALBUM *album = NULL;
		author->albums = (ALBUM**)calloc(author->albKol, sizeof(ALBUM*));
		if (author->albums != NULL) {
			for (unsigned i = 0; i < author->albKol; i++) {
				albumAdress = getStrFromFile(file);
				albumFile = fopen(albumAdress, "r");
				if (albumFile == NULL) {
					printf("������ �������� ����� %s.\n", albumAdress);
				}
				else {
					author->albums[i] = getAlbumFromFile(albumFile);
					if (author->albums[i] == NULL) {
						author->albKol = i;
					}
					else {
						author->albums[i]->author = author;
						fixSongAuthor(author->albums[i]);
					}
				}
				fclose(albumFile);
			}
		}
		else {
			puts("������. ������������ ������.");
			author->albKol = 0;
			author = deleteAuthor(author);
			return NULL;
		}
	}
	else {
		puts("������. ������������ ������.");
	}
	return author;
}
//��������

AUTHOR *getAuthorFromKeyboard() {
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("������� �����������: ");
	author->name = getStr();
	do {
		system("cls");
		printf("������� ���������� ��������: ");
		author->albKol = strToUnsigned(getStr());
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
					author = deleteAuthor(author);
				}
				break;
			}
		}
	}
	else {
		author->albKol = 0;
		author = deleteAuthor(author);
	}
	return author;
}
//��������

AUTHOR *getAuthor() {
	AUTHOR *author = NULL;
	char choise, choise2;
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
			album = deleteAlbum(album);
		}
	}
}
//��������

void printAuthor(AUTHOR *author) {
	system("cls");
	if (author != NULL) {
		printf("������� ����������� %s:\n", author->name);
		for (unsigned i = 0; i < author->albKol; i++) {
			printf("%d - %s\n", i + 1, author->albums[i]->name);
		}
	}
	else {
		puts("������� �� ����������.");
	}
}
//��������

AUTHOR *deleteAlbumFromAuthor(AUTHOR *author) {
	unsigned num = 0;
	char choise;
	do {
		system("cls");
		printAuthor(author);
		puts("������� ����� �������, ������� ������ �������: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			if (author->albKol == 1) {
				author = deleteAuthor(author);
			}
			else {
				author->albKol--;
				author->albums[num - 1] = deleteAlbum(author->albums[num - 1]);
				for (unsigned i = num - 1; i < author->albKol; i++) {
					author->albums[i] = author->albums[i + 1];
				}
				author->albums = (ALBUM**)realloc(author->albums, author->albKol * sizeof(ALBUM*));
			}
			break;
		}
		else {
			do {
				system("cls");
				puts("������� � ����� ������� ���. ������ ������ �����?");
				puts("(1) - ��.");
				puts("(2) - ���.");
				choise = _getch();
				switch (choise) {
				case '1': {
					num = 0;
					break;
				}
				case '2': {
					num = 1;
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
	} while (num == 0);
	return author;
}
//��������

AUTHOR *changeAlbumInAuthor(AUTHOR *author) {
	char choise;
	unsigned num;
	do {
		system("cls");
		printAuthor(author);
		puts("������� ����� �������, ������� ������ ��������: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			author->albums[num - 1] = changeAlbum(author->albums[num - 1]);
			break;
		}
		else {
			do {
				system("cls");
				puts("������� � ����� ������� ���. ������ ������ �����?");
				puts("(1) - ��.");
				puts("(2) - ���.");
				choise = _getch();
				switch (choise) {
				case '1': {
					num = 0;
					break;
				}
				case '2': {
					num = 1;
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
	} while (num == 0);
	return author;
}
//��������

AUTHOR *changeAuthor(AUTHOR *author) {
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
			author = changeAlbumInAuthor(author);
			break;
		}
		case '4': {
			author = deleteAlbumFromAuthor(author);
			break;
		}
		case '5': {
			author = deleteAuthor(author);
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 51);
	return author;
}
//��������