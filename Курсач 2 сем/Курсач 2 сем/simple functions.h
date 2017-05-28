#include <conio.h>
#include <iostream>
#pragma warning (disable: 4996)

char* getStr(){
	char ch;
	char *str = NULL;
	char *test = NULL;
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
			test = (char*)realloc(str, kol * sizeof(char));
			if (test != NULL) {
				str = test;
				str[kol - 1] = ch;
				printf("%c", ch);
			}
			else {
				puts("\n������. ������������ ������. ���� �������.");
				break;
			}
		}
	} while (ch != '\r');
	if (str != NULL) {
		str[kol - 1] = '\0';
		return str;
	}
	else {
		return "\0";
	}
}
//��������

char* getStrFromFile(FILE *file){
	char ch;
	char *str = NULL;
	char *test = NULL;
	unsigned kol = 0;
	do{
		ch = getc(file);
		if (ch == EOF) {
			ch = '\n';
		}
		kol++;
		test = (char*)realloc(str, kol*sizeof(char));
		if (test != NULL) {
			str = test;
			str[kol - 1] = ch;
		}
		else {
			puts("\n������. ������������ ������. ���� �������.");
			kol--;
			break;
		}
	} while (ch != '\n');
	if (str != NULL) {
		str[kol - 1] = '\0';
		return str;
	}
	else {
		return "\0";
	}
}
//��������

unsigned strToUnsigned(char *str){
	double num = 0;
	for (unsigned i = 0; str[i] != '\0'; i++){
		if (str[i] < 48 || str[i] > 57){
			puts("������! ���������� ������������� ������ � �����!");
			return 0;
		}
		num = num * 10 + str[i] - 48;
		if (num > INT_MAX) {
			puts("������. ����� ������� ������.");
			return 0;
		}
	}
	return (unsigned)num;
}
//��������

bool fileNull(){
	char choise;
	do{
		system("cls");
		puts("������ �������� �����. ������ ������ ����?");
		puts("(1) - ��.");
		puts("(2) - ���.");
		choise = _getch();
		switch (choise){
		case '1': {
			return true;
		}
		case '2': {
			return false;
		}
		default:{
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while ((choise < 49) || (choise > 50));
}
//��������

void FAQ(){
	FILE *file;
	char ch;
	file = fopen("files/�������.txt", "r");
	if (file == NULL) {
		system("cls");
		puts("������ �������� ����� �������.");
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
//��������
