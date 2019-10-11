//Orshak Ivan, 2017

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int crpt_txt(char* FilePath, int Key)
{
	char c;
	size_t Cnt = 0;
	FILE* Fin;
	FILE* Fout;
	char FilePath_Enc[211] = "_encrypted_";
	size_t i;
	unsigned char* TxtIn;

	if (FilePath == NULL)
		return 1;
	if (Key < 0 || Key > 26)
		return 2;

	if ((Fin = fopen(FilePath, "rt")) == NULL)
		return 3;

	while ((c = fgetc(Fin)) != EOF)
		Cnt++;

	if (Cnt == 0)
	{
		fclose(Fin);
		return 7;
	}

	strcat(FilePath_Enc, FilePath);
	if ((Fout = fopen(FilePath_Enc, "wt")) == NULL)
	{
		fclose(Fin);
		return 3;
	}

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
			TxtIn[i] += Key;

			if (TxtIn[i] > 'z')
				TxtIn[i] -= 26;
		}
		else if (TxtIn[i] >= 'A' && TxtIn[i] <= 'Z')
		{
			TxtIn[i] += Key;

			if (TxtIn[i] > 'Z')
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