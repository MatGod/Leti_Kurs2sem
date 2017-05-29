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
//Работает

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
					printf("Ошибка открытия файла %s.\n", albumAdress);
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
			puts("Ни один альбом не введён. Исполнитель не создан.");
		}
	}
	else {
		puts("Ошибка. Недостаточно памяти.");
	}
	return author;
}
//Работает

AUTHOR *getAuthorFromKeyboard() {
	bool a;
	AUTHOR *author = (AUTHOR*)calloc(1, sizeof(ALBUM));
	char choise = '1';
	system("cls");
	printf("Введите исполнителя: ");
	author->name = getStr();
	do {
		system("cls");
		printf("Введите количество альбомов: ");
		author->albKol = strToUnsigned(getStr());
		if (author->albKol > 0) {
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
//Работает

AUTHOR *getAuthor() {
	AUTHOR *author = NULL;
	char choise;
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
	bool a;
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
			album = deleteAlbum(album, &a);
		}
	}
	else {
		puts("Добавить альбом не удалось.");
	}
}
//Работает

void printAuthor(AUTHOR *author) {
	system("cls");
	printf("Альбомы исполнителя %s:\n", author->name);
	for (unsigned i = 0; i < author->albKol; i++) {
		printf("%d - %s\n", i + 1, author->albums[i]->name);
	}
}
//Работает

unsigned notAlbumInAuthor() {
	char choise;
	do {
		system("cls");
		puts("Альбома с таким номером нет. Ввести другой номер?");
		puts("(1) - Да.");
		puts("(2) - Нет.");
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
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 50);
}
//Работает

AUTHOR *deleteAlbumFromAuthor(AUTHOR *author, bool *chB) {
	unsigned num = 0;
	do {
		system("cls");
		printAuthor(author);
		puts("Введите номер альбома, который хотите удалить: ");
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
//Работает

AUTHOR *changeAlbumInAuthor(AUTHOR *author, bool *chB) {
	unsigned num;
	do {
		system("cls");
		printAuthor(author);
		puts("Введите номер альбома, который хотите изменить: ");
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
//Работает

AUTHOR *changeAuthor(AUTHOR *author, bool *chB) {
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
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while (choise < 49 || choise > 53);
	return author;
}
//Работает