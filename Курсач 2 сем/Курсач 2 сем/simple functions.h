#include <conio.h>
#include <iostream>
#pragma warning (disable: 4996)

char* getStr(){
	char ch;
	char *str = NULL;
	unsigned kol = 0;
	do{
		ch = _getch();
		if (ch == '\b') {
			if (kol > 0) {
				kol--;
				str = (char*)realloc(str, kol * sizeof(char));
				printf("\b \b");
			}
		}
		else{
			kol++;
			str = (char*)realloc(str, kol*sizeof(char));
			str[kol - 1] = ch;
			printf("%c", ch);
		}
	} while (ch != '\r');
	str[kol - 1] = '\0';
	return str;
}
//Работает

char* getStrFromFile(FILE *file){
	char ch;
	char *str = NULL;
	unsigned kol = 0;
	do{
		ch = getc(file);
		kol++;
		str = (char*)realloc(str, kol*sizeof(char));
		str[kol - 1] = ch;
	} while (ch != '\n');
	str[kol - 1] = '\0';
	return str;
}
//Работает

unsigned strToUnsigned(char *str){
	double num = 0;
	for (unsigned i = 0; str[i] != '\0'; i++){
		if (str[i] < 48 || str[i] > 57){
			puts("Ошибка! Невозможно преобразовать строку в число!");
			return 0;
		}
		num = num * 10 + str[i] - 48;
		if (num > INT_MAX) {
			puts("Ошибка. Число слишком велико.");
			return 0;
		}
	}
	return (unsigned)num;
}
//Работает

bool fileNull(){
	char choise;
	do{
		system("cls");
		puts("Ошибка открытия файла. Ввести другой путь?");
		puts("(1) - Да.");
		puts("(2) - Нет.");
		choise = _getch();
		switch (choise){
		case '1': {
			return true;
		}
		case '2': {
			return false;
		}
		default:{
			puts("Пункта с таким номером нет!");
			system("pause");
			break;
		}
		}
	} while ((choise < 49) || (choise > 50));
}
//Работает

void FAQ(){
	FILE *file;
	char ch;
	file = fopen("files/Справка.txt", "r");
	if (file == NULL) {
		system("cls");
		puts("Ошибка открытия файла справки.");
	}
	else {
		system("cls");
		while ((ch = getc(file)) != EOF) {
			printf("%c", ch);
		}
		puts("");
		fclose(file);
	}
	system("pause");
}
//Работает