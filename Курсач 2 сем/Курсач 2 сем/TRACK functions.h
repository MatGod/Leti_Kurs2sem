#include "BASE functions.h"

TRACK *setPlaylist(TRACK *playlist){
	return playlist;
}

TRACK *changePlaylist(TRACK *playlist){
	char choise, choise4;
	system("cls");
	puts("������� ������� � ��������������� ������� ������:");
	puts("(1) - �������� �����.");
	puts("(2) - ������� �����.");
	puts("(3) - ����������� ��������.");
	puts("(4) - ���������� ��������.");
	choise = _getch();
	do {
		switch (choise) {
		case '1': { // ��������
			system("cls");
			puts("������� ������� � ��������������� ������� ������:");
			puts("��������:");
			puts("(1) - ��� ����� ������ �����������.");
			puts("(2) - ��� ����� �� ������ �������.");
			puts("(3) - ��� ����� ������ ���� ������.");
			puts("(4) - ���������� �����.");
			choise4 = _getch();
			do{
				switch (choise4) {
				case '1':{
					system("cls");

					break;
				}
				case '2': {

					break;
				}
				case '3': {

					break;
				}
				case '4': {

					break;
				}
				default:{
					system("cls");
					puts("������ � ����� ������� ���!");
					system("pause");
					break;
				}
				}
			} while ((choise4 < 49) || (choise4 > 52));
			break;
		}
		case '2': {
			break;
		}
		case '3': {
			break;
		}
		case '4': {
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while ((choise < 49) || (choise > 52));
	system("pause");
	return playlist;
}

TRACK *deletePlaylist(TRACK *playlist){
	return playlist;
}