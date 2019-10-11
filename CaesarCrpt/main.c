//Orshak Ivan, group #7362, 2017

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "encryption.h"
#include "decryption.h"

int main()
{
	char C = 0;
	size_t Err_Catcher = 0;
	char* Errors[] = { "Program finished correctly!", "Invalid 1st argument!", "Invalid 2nd argument!",
		"Cannot open or create file!", "Unable to allocate memory!", "Error reading file!",
		"Error writing in file!", "File is empty!", "File wasn't closed" };
	char FilePath[200];
	int Key;
	
	SetDbgMemHooks();

	while (C != '0')
	{
		printf("1.Encrypt text\n2.Decrypt text\n0.Exit\n");

		switch (C = _getch())
		{
		case '1':
			system("cls");
			printf("Enter path to file: ");
			scanf("%s", FilePath);
			printf("Enter encryption key: ");
			scanf("%d", &Key);
			Err_Catcher = crpt_txt(FilePath, Key);
			printf("%s\n", Errors[Err_Catcher]);
			break;
		case '2':
			system("cls");
			printf("Enter path to file: ");
			scanf("%s", FilePath);
			Err_Catcher = decrpt_txt(FilePath);
			printf("%s\n", Errors[Err_Catcher]);
			break;
		case '0':
			return 0;
		default:
			printf("\nUnknown command!");
		}

		printf("\nTap any key to continue...");
		_getch();
		system("cls");
	}
	_getch();
	return 0;
}
