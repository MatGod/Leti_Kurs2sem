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
//Работает

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
					printf("Ошибка открытия файла %s.\n", albumAdress);
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
			puts("Ошибка. Недостаточно памяти.");
			author->albKol = 0;
			author = deleteAuthor(author);
			return NULL;
		}
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return author;
}
//Работает

AUTHOR *getAuthorFromKeyboard() {
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("Введите исполнителя: ");
	author->name = getStr();
	do {
		system("cls");
		printf("Введите количество альбомов: ");
		author->albKol = strToUnsigned(getStr());
		author->albums = (ALBUM**)calloc(author->albKol, sizeof(SONG*));
		if (author->albums == NULL) {
			do {
				system("cls");
				puts("Недостаточно памяти! Ввести другое количество альбомов?");
				puts("(1) - Да.");
				puts("(2) - Нет.");
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
					puts("Пункта с таким номером нет!");
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
//Работает

AUTHOR *getAuthor() {
	AUTHOR *author = NULL;
	char choise, choise2;
	FILE *file = NULL;
	do {
		system("cls");
		puts("Каким образом ввести исполнителя?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с исполнителем: ");
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
		puts("Создать исполнителя не удалось.");
	}
	else {
		puts("Исполнитель успешно добавлен в базу.");
	}
	system("pause");
	return author;
}
//Работает

void addAlbumToAuthor(AUTHOR *author) {
	ALBUM *album = NULL;
	FILE *albumFile = NULL;
	char choise;
	do {
		system("cls");
		puts("Каким образом добавить альбом исполнителю?");
		puts("(1) - Считать из файла.");
		puts("(2) - Ввести с клавиатуры.");
		choise = _getch();
		switch (choise) {
		case '1': {
			do {
				system("cls");
				puts("Введите адрес файла с альбомом: ");
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
			puts("Пункта с таким номером нет!");
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
			printf("Альбом %s успешно добавлен исполнителю %s.\n", album->name, author->name);
		}
		else {
			puts("Ошибка. Недостаточно памяти.");
			album = deleteAlbum(album);
		}
	}
}
//Работает

void printAuthor(AUTHOR *author) {
	system("cls");
	if (author != NULL) {
		printf("Альбомы исполнителя %s:\n", author->name);
		for (unsigned i = 0; i < author->albKol; i++) {
			printf("%d - %s\n", i + 1, author->albums[i]->name);
		}
	}
	else {
		puts("Альбома не существует.");
	}
}
//Работает

AUTHOR *deleteAlbumFromAuthor(AUTHOR *author) {
	unsigned num = 0;
	char choise;
	do {
		system("cls");
		printAuthor(author);
		puts("Введите номер альбома, который хотите удалить: ");
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
				puts("Альбома с таким номером нет. Ввести другой номер?");
				puts("(1) - Да.");
				puts("(2) - Нет.");
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
					puts("Пункта с таким номером нет!");
					system("pause");
					break;
				}
				}
			} while (choise < 49 || choise > 50);
		}
	} while (num == 0);
	return author;
}
//Работает

AUTHOR *changeAlbumInAuthor(AUTHOR *author) {
	char choise;
	unsigned num;
	do {
		system("cls");
		printAuthor(author);
		puts("Введите номер альбома, который хотите изменить: ");
		num = strToUnsigned(getStr());
		if (num > 0 && num <= author->albKol) {
			author->albums[num - 1] = changeAlbum(author->albums[num - 1]);
			break;
		}
		else {
			do {
				system("cls");
				puts("Альбома с таким номером нет. Ввести другой номер?");
				puts("(1) - Да.");
				puts("(2) - Нет.");
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
					puts("Пункта с таким номером нет!");
					system("pause");
					break;
				}
				}
			} while (choise < 49 || choise > 50);
		}
	} while (num == 0);
	return author;
}
//Работает

AUTHOR *changeAuthor(AUTHOR *author) {
	char choise;
	do {
		system("cls");
		puts("Что вы хотите сделать с исполнителем?");
		puts("(1) - Показать список альбомов.");
		puts("(2) - Добавить альбом исполнителю.");
		puts("(3) - Посмотреть/изменить один из альбомов.");
		puts("(4) - Удалить альбом у исполнителя.");
		puts("(5) - Удалить исполнителя.");
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
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 51);
	return author;
}
//Работает