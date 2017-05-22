#include "stdafx.h"
#include "TRACK functions.h"
#pragma warning (disable: 4996)

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	char choise1, choise2;
	char ch;
	AUTHOR *base = NULL;
	TRACK *playlist = NULL;
	do {
		system("cls");
		puts("������� ������� � ��������������� ������� ������:");
		puts("(1) - ������ � ����� �����.");
		puts("(2) - ������ � ������� ����������.");
		puts("(3) - ������� � ���������.");
		puts("��� ������ �� ��������� ������� 0.");
		choise1 = _getch();
		switch (choise1)
		{
		case '1': {
			system("cls");
			puts("������� ������� � ��������������� ������� ������:");
			puts("(1) - ������� ����� ����.");
			puts("(2) - �������� ����� � ����.");
			puts("(3) - ������� ����� �� ����.");
			puts("(4) - ������� ����.");
			choise2 = _getch();
			do {
				switch (choise2) {
				case '1': {
					base = getBase(base);
					break;
				}
				case '2': {
					base = addSongToBase(base);
					break;
				}
				case '3': {
					base = deleteSongFromBase(base);
					break;
				}
				case '4': {
					base = deleteBase(base);
					break;
				}
				default:{
					system("cls");
					puts("������ � ����� ������� ���!");
					system("pause");
					break;
				}
				}
			} while ((choise2 < 49) || (choise2 > 52));
			break;
		}
		case '2': { // ������ � ����������
			system("cls");
			puts("������� ������� � ��������������� ������� ������:");
			puts("(1) - ������� ����� ��������.");
			puts("(2) - ������������� ������� ��������.");
			puts("(3) - ������� ������� ��������.");
			choise2 = _getch();
			do {
				switch (choise2) {
				case '1': {
					playlist = setPlaylist(playlist);
					break;
				}
				case '2': {
					playlist = changePlaylist(playlist);
					break;
				}
				case '3': {
					playlist = deletePlaylist(playlist);
					break;
				}
				default: {
					system("cls");
					puts("������ � ����� ������� ���!");
					system("pause");
					break;
				}
				}
			} while ((choise2 < 49) || (choise2 > 51));
			break;
		}
		case '3': { // �������
			FAQ();
			break;
		}
		case '0': {
			break;
		}
		default: {
			system("cls");
			puts("������ � ����� ������� ���!");
			system("pause");
			break;
		}
		}
	} while (choise1 != '0');
	puts("����� �� ���������...");
	_getch();
	return 0;
}