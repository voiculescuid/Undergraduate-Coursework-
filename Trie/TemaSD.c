/* VOICULESCU Ion - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "head.h"

int main(int argc, char *argv[])
{
	int OP, IN, ARR;
	char *ins, *w;
	char up[5000];
	long int pos;
	ATrie T;

	FILE *inf = fopen(argv[1], "rt");
	FILE *outf = fopen(argv[2], "wt");

	fscanf(inf, "%d", &OP);

	T = NOD();

	while (OP)
	{
		fscanf(inf, "%s", up);
		ins = strdup(up);

		if (strcmp(ins, "add") == 0)
			IN = 1;
		if (strcmp(ins, "remove") == 0)
			IN = 2;
		if (strcmp(ins, "find") == 0)
			IN = 3;
		if (strcmp(ins, "find_longest_prefix") == 0)
			IN = 4;
		if (strcmp(ins, "find_all_with_prefix") == 0)
			IN = 5;
		if (strcmp(ins, "mean_length") == 0)
			IN = 6;
		free(ins);
		switch (IN)
		{


		case 1:

			fscanf(inf, "%s", up);
			w = strdup(up);

			ADD(T, w);
			free(w);
			break;



		case 2:

			fscanf(inf, "%s", up);
			w = strdup(up);

			RM(T, w);
			free(w);
			break;



		case 3:

			fscanf(inf, "%s", up);
			w = strdup(up);

			FIND(T, w, outf);
			free(w);
			break;



		case 4:

			fscanf(inf, "%s", up);
			w = strdup(up);

			LONGEST(T, w, outf);
			free(w);
			break;



		case 5:
			if (fgetc(inf) == ' ')
			{
				pos = ftell(inf);
				ARR = fgetc(inf);
				if (ARR != '\n')
				{
					fseek(inf, pos, SEEK_SET);
					fscanf(inf, "%s", up);
					w = strdup(up);
				}
				else
					w = calloc(1, (T->length + 1) * sizeof(char));
			}
			else
				w = calloc(1, (T->length + 1) * sizeof(char));

			ALLPREFIX(T, w, outf);
			free(w);
			break;



		case 6:
			if (fgetc(inf) == ' ')
			{
				pos = ftell(inf);
				ARR = fgetc(inf);
				if (ARR != '\n')
				{
					fseek(inf, pos, SEEK_SET);
					fscanf(inf, "%s", up);
					w = strdup(up);
				}
				else
					w = calloc(1, (T->length + 1) * sizeof(char));
			}
			else
				w = calloc(1, (T->length + 1) * sizeof(char));

			MEAN(T, w, outf);
			free(w);
			break;
		}
		OP--;
	}

	FREET(T);
	fclose(inf);
	fclose(outf);

	return 0;
}
