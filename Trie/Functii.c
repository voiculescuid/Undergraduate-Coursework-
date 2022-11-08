/* VOICULESCU Ion - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "head.h"

//POZITIA CARACTERULUI

int ind(char *b)
{

	char a[1];
	memcpy(a, b, 1);

	if (strcmp(a, "0") == 0)
		return 0;
	if (strcmp(a, "1") == 0)
		return 1;
	if (strcmp(a, "2") == 0)
		return 2;
	if (strcmp(a, "3") == 0)
		return 3;
	if (strcmp(a, "4") == 0)
		return 4;
	if (strcmp(a, "5") == 0)
		return 5;
	if (strcmp(a, "6") == 0)
		return 6;
	if (strcmp(a, "7") == 0)
		return 7;
	if (strcmp(a, "8") == 0)
		return 8;
	if (strcmp(a, "9") == 0)
		return 9;
	if (strcmp(a, "a") == 0)
		return 10;
	if (strcmp(a, "b") == 0)
		return 11;
	if (strcmp(a, "c") == 0)
		return 12;
	if (strcmp(a, "d") == 0)
		return 13;
	if (strcmp(a, "e") == 0)
		return 14;
	if (strcmp(a, "f") == 0)
		return 15;
	if (strcmp(a, "g") == 0)
		return 16;
	if (strcmp(a, "h") == 0)
		return 17;
	if (strcmp(a, "i") == 0)
		return 18;
	if (strcmp(a, "j") == 0)
		return 19;
	if (strcmp(a, "k") == 0)
		return 20;
	if (strcmp(a, "l") == 0)
		return 21;
	if (strcmp(a, "m") == 0)
		return 22;
	if (strcmp(a, "n") == 0)
		return 23;
	if (strcmp(a, "o") == 0)
		return 24;
	if (strcmp(a, "p") == 0)
		return 25;
	if (strcmp(a, "q") == 0)
		return 26;
	if (strcmp(a, "r") == 0)
		return 27;
	if (strcmp(a, "s") == 0)
		return 28;
	if (strcmp(a, "t") == 0)
		return 29;
	if (strcmp(a, "u") == 0)
		return 30;
	if (strcmp(a, "v") == 0)
		return 31;
	if (strcmp(a, "w") == 0)
		return 32;
	if (strcmp(a, "x") == 0)
		return 33;
	if (strcmp(a, "y") == 0)
		return 34;
	if (strcmp(a, "z") == 0)
		return 35;
}

//POZITIE IN CHAR

char *chr(int a)
{
	if (a == 0)
		return "0";
	if (a == 1)
		return "1";
	if (a == 2)
		return "2";
	if (a == 3)
		return "3";
	if (a == 4)
		return "4";
	if (a == 5)
		return "5";
	if (a == 6)
		return "6";
	if (a == 7)
		return "7";
	if (a == 8)
		return "8";
	if (a == 9)
		return "9";
	if (a == 10)
		return "a";
	if (a == 11)
		return "b";
	if (a == 12)
		return "c";
	if (a == 13)
		return "d";
	if (a == 14)
		return "e";
	if (a == 15)
		return "f";
	if (a == 16)
		return "g";
	if (a == 17)
		return "h";
	if (a == 18)
		return "i";
	if (a == 19)
		return "j";
	if (a == 20)
		return "k";
	if (a == 21)
		return "l";
	if (a == 22)
		return "m";
	if (a == 23)
		return "n";
	if (a == 24)
		return "o";
	if (a == 25)
		return "p";
	if (a == 26)
		return "q";
	if (a == 27)
		return "r";
	if (a == 28)
		return "s";
	if (a == 29)
		return "t";
	if (a == 30)
		return "u";
	if (a == 31)
		return "v";
	if (a == 32)
		return "w";
	if (a == 33)
		return "x";
	if (a == 34)
		return "y";
	if (a == 35)
		return "z";
}

//FREE TRIE

void FREET(ATrie T)
{
	int i;
	if (!T)
		return;

	for (i = 0; i <= 35; i++)
		FREET(T->sons[i]);

	free(T);
}

//ALOCARE NOD

ATrie NOD()
{
	ATrie X;
	int i;
	X = (struct Trie *)malloc(sizeof(struct Trie));
	if (X == NULL)
	{
		printf("Eroare alocare!");
	}

	X->use = 0;
	X->term = 0;
	X->length = 0;
	for (i = 0; i <= 35; i++)
		X->sons[i] = NULL;
	return X;
}

//EXISTENTA UNUI SIR DE CARACTERE

int IS(ATrie T, char *w)
{
	ATrie X = T;
	int i, len, OK = 0, loc;
	len = strlen(w);

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);
		if (X->sons[loc] == NULL)
		{
			OK = 1;
			break;
		}

		X = X->sons[loc];
	}
	if (OK == 1)
		return 0;

	if (OK == 0 && X->term == 1)
		return 1;
	else
		return 0;
}

//FUNCTIE DE ADAUGARE

int ADD(ATrie T, char *w)
{
	int i, len, loc, OK, add = 1;

	len = strlen(w);

	OK = IS(T, w);

	if (len > T->length)
		T->length = len;

	add = T->length;

	if (OK == 1)
		return 0;
	else
	{
		T->use++;
		for (i = 0; i < len; i++)
		{
			loc = ind(&w[i]);
			if (T->sons[loc] == NULL)
				T->sons[loc] = NOD();

			T = T->sons[loc];
			T->use++;
			T->length = add;
		}
		T->term = 1;
	}
	return 1;
}

//FUNCTIE DE STERGERE

int RM(ATrie T, char *w)
{
	ATrie X, Y = NULL, Z = NULL;
	X = T;
	int i, len, loc, OK;
	OK = IS(T, w);

	if (OK == 0)
		return 0;

	if (w == NULL)
		return 1;

	T->use--;
	len = strlen(w);

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);

		Y = X->sons[loc];
		Z = X->sons[loc];
		--Y->use;
		if (Y->use == 0)
		{
			X->sons[loc] = NULL;
			FREET(Z);
			return 1;
		}
		X = Y;
	}

	if (Y != NULL)
		Y->term = 0;

	return 1;
}

//FUNCTIE DE CAUTARE

void FIND(ATrie T, char *w, FILE *outf)
{
	ATrie X = T;
	int i, len = strlen(w), OK = 0, loc;

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);
		if (X->sons[loc] == NULL)
		{
			OK = 1;
			fprintf(outf, "False\n");
			break;
		}

		X = X->sons[loc];
	}
	if (OK == 1)
		return;

	if (OK == 0 && X->term == 1)
		fprintf(outf, "True\n");
	else
		fprintf(outf, "False\n");
}

//FUNCTEI PENTRU CEL MAI LUNG PREFIX

void LONGEST(ATrie T, char *w, FILE *outf)
{
	ATrie X;
	int i, len, loc;

	len = strlen(w);

	X = T;
	loc = ind(&w[0]);
	if (X->sons[loc] == NULL)
	{
		fprintf(outf, "None\n");
		return;
	}

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);
		if (X->sons[loc] != NULL)
		{
			fprintf(outf, "%c", w[i]);
			X = X->sons[loc];
		}
		else
		{
			fprintf(outf, "\n");
			return;
		}
	}
	fprintf(outf, "\n");
}

//RETURNEAZA PRIMUL CUVANT DIN TREE(ALFABETIC)

void WORD(ATrie T, char *w)
{
	int i, h = -1;

	if (T->term == 1)
	{
		T->term = 0;
		return;
	}

	for (i = 0; i <= 35; i++)
	{
		if (T->sons[i] != NULL)
		{
			T = T->sons[i];
			h = i;
			break;
		}
	}

	if (h != -1)
		strcat(w, chr(h));

	if (T->term != 1)
		WORD(T, w);
}

//AFISARE TRIE

void AFITRIE(ATrie T, char *x, FILE *outf)
{
	ATrie X = NOD();
	int count = 0;
	char *w;

	count = T->use;

	while (count)
	{
		w = calloc(1, (T->length + 1) * sizeof(char));
		WORD(T, w);
		fprintf(outf, "%s%s", x, w);
		RM(T, w);
		ADD(X, w);
		free(w);
		count--;

		if (count)
			fprintf(outf, " ");
	}
	fprintf(outf, "\n");

	count = X->use;

	while (count)
	{
		w = calloc(1, (T->length + 1) * sizeof(char));
		WORD(X, w);
		RM(X, w);
		ADD(T, w);
		free(w);
		count--;
	}
	FREET(X);
}

//FUNCTIE CARE AFISEAZA TOATE CUVINETELE CU PREFIXUL [w]

void ALLPREFIX(ATrie T, char *w, FILE *outf)
{
	int len, loc, i;
	len = strlen(w);

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);
		if (T->sons[loc] == NULL)
		{
			fprintf(outf, "None\n");
			return;
		}
		T = T->sons[loc];
	}
	AFITRIE(T, w, outf);
}

//CALCULAREA LUNGIMI CUVINETELOR CU UN ANUMIT PREFIX  

void LENGTH(ATrie T, int add, FILE *outf)
{
	int num = 0, sum = 0, count;
	char *w;
	ATrie X = NOD();

	count = T->use;

	if (T->use == 0)
	{
		fprintf(outf, "0");
		return;
	}

	while (count)
	{
		w = calloc(1, (T->length + 1) * sizeof(char));
		WORD(T, w);
		sum = sum + strlen(w);
		RM(T, w);
		ADD(X, w);
		free(w);
		count--;
	}

	count = X->use;

	while (count)
	{
		w = calloc(1, (T->length + 1) * sizeof(char));
		num++;
		WORD(X, w);
		RM(X, w);
		ADD(T, w);
		free(w);
		count--;
	}

	sum = sum + num * add;

	fprintf(outf, "%.3f\n", (float)sum / num);

	FREET(X);
}

//GASIRE PREFIXULUI [w]

void MEAN(ATrie T, char *w, FILE *outf)
{
	int len, loc, i;

	len = strlen(w);

	for (i = 0; i < len; i++)
	{
		loc = ind(&w[i]);
		if (T->sons[loc] == NULL)
		{
			fprintf(outf, "0\n");
			return;
		}
		T = T->sons[loc];
	}
	LENGTH(T, strlen(w), outf);
}
