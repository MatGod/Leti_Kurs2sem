#include <conio.h>
#include <iostream>
#pragma warning (disable: 4996)

char* getStr(){
	char ch;
	char *str = NULL;
	unsigned kol = 0;
	do{
		ch = _getch();
		if (ch == '\b' && kol > 0){
			kol--;
			str = (char*)realloc(str, kol*sizeof(char));
			printf("\b \b");
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

char* getStrFromFile(FILE *file){
	char ch;
	char *str = NULL;
	unsigned kol = 0;
	do{
		ch = fscanf(file, "%c");
		kol++;
		str = (char*)realloc(str, kol*sizeof(char));
		str[kol - 1] = ch;
	} while (ch != '\n');
	str[kol - 1] = '\0';
	return str;
}

unsigned getUnsigned(){
	unsigned num = 0, i;
	char *str;
	bool right;
	do{
		right = true;
		str = getStr();
		i = 0;
		do{
			if (str[i] < 48 || str[i] > 57){
				right = false;
				printf("Ошибка ввода. Введите положительное число или 0...\n");
				break;
			}
			i++;
		} while (str[i-1] != '\0');
	} while (!right);
	return num;
}

unsigned strToUnsigned(char *str){
	unsigned num = 0;
	for (unsigned i = 0; str[i] != '\0'; i++){
		if (str[i] < 48 || str[i] > 57){
			puts("Ошибка! Невозможно преобразовать строку в число!");
			return 0;
		}
		num = num * 10 + str[i] - 48;
	}
	return num;
}

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