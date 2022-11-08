/* VOICULESCU Ion - 315CB */

typedef struct Trie
{
	struct Trie *sons[36];
	int use;
	int term;
	int length;

} Trie, *ATrie;


//FUNCTII

int ind(char *b);
char *chr(int a);
ATrie NOD();
int IS(ATrie T, char *w);
int ADD(ATrie T, char *w);
int RM(ATrie T, char *w);
void FIND(ATrie T, char *w, FILE * outf);
void LONGEST(ATrie T, char *w, FILE *outf);
void WORD(ATrie T, char *word);
void AFITRIE(ATrie T, char *x, FILE *outf);
void ALLPREFIX(ATrie T, char *w, FILE *outf);
void LENGTH(ATrie T, int add, FILE *outf);
void MEAN(ATrie T, char *w, FILE *outf);
void FREET(ATrie T);
