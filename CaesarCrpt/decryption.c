//Orshak Ivan, 2017

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decrpt_txt(char* FilePath)
{
	char c;
	size_t Cnt = 0;
	FILE* Fin;
	char FilePath_Dec[211] = "_decrypted_";
	FILE* Fout;
	size_t i;
	int Key;
	int LetVals[26] = { 0 };
	int Max = 0;
	unsigned char* TxtIn;

	if (FilePath == NULL)
		return 1;

	if ((Fin = fopen(FilePath, "rt")) == NULL)
		return 3;

	while ((c = fgetc(Fin)) != EOF)
	{
		if (c >= 'a' && c <= 'z')
			LetVals[c - 'a']++;
		else if (c >= 'A' && c <= 'Z')
			LetVals[c - 'A']++;

		Cnt++;
	}

	if (Cnt == 0)
	{
		fclose(Fin);
		return 7;
	}

	strcat(FilePath_Dec, FilePath);
	if ((Fout = fopen(FilePath_Dec, "wt")) == NULL)
	{
		fclose(Fin);
		return 3;
	}

	c = 0;

	for (i = 0; i < 26; i++)
		if (LetVals[i] > Max)
		{
			Max = LetVals[i];
			c = i + 'a';
		}

	Key = c - 'e';

	rewind(Fin);

	if ((TxtIn = (char*)calloc(Cnt, sizeof(char))) == NULL)
	{
		fclose(Fin);
		fclose(Fout);
		return 4;
	}

	if ((fread(TxtIn, sizeof(char), Cnt, Fin)) != Cnt)
	{
		fclose(Fin);
		fclose(Fout);
		free(TxtIn);
		return 5;
	}

	if (fclose(Fin) != 0)
	{
		fclose(Fout);
		free(TxtIn);
		return 8;
	}

	for (i = 0; i < Cnt; i++)
	{
		if (TxtIn[i] >= 'a' && TxtIn[i] <= 'z')
		{
			TxtIn[i] -= Key;

			if (TxtIn[i] < 'a')
				TxtIn[i] += 26;
			else if (TxtIn[i] > 'z')
				TxtIn[i] -= 26;
		}
		else if (TxtIn[i] >= 'A' && TxtIn[i] <= 'Z')
		{
			TxtIn[i] -= Key;

			if (TxtIn[i] < 'A')
				TxtIn[i] += 26;
			else if (TxtIn[i] > 'Z')
				TxtIn[i] -= 26;
		}
	}

	if ((fwrite(TxtIn, sizeof(char), Cnt, Fout)) != Cnt)
	{
		fclose(Fout);
		free(TxtIn);
		return 6;
	}

	if (fclose(Fout) != 0)
	{
		free(TxtIn);
		return 8;
	}

	free(TxtIn);

	return 0;
}