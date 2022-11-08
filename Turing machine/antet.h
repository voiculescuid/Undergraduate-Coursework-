#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10000

typedef struct TR {
	char *current_state;
	char *tape1_read_symbol;
	char *tape2_read_symbol;
	char *next_state;
	char *tape1_write_symbol;
	char *tape1_direction;
	char *tape2_write_symbol;
	char *tape2_direction;
} TR;

typedef struct BAN {
	char *current_state;

	char input1[MAX];
	int point1;
	int len1;

	char input2[MAX];
	int point2;
	int len2;
} BAN;
