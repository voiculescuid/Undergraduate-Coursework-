#include"antet.h"

int CHECK(BAN a, int N, char *F[N]);
int TRANS(BAN a, int P, TR T[P]);


int main()
{
FILE * in = fopen("task1.in", "r");
FILE * out = fopen("task1.out", "w");
int N,i,M,P;
char buff[101];
fscanf(in, "%d", &N);

char *S[N];

for(i=0;i<N;i++)
	{
	fscanf(in, "%s",buff);
	S[i]=(char *) calloc(strlen(buff)+1, sizeof(char));
	strcpy(S[i], buff);
	} 

fscanf(in, "%d", &M);

char *F[M];

for(i=0;i<M;i++)
	{
        fscanf(in, "%s",buff);
	F[i]=(char *) calloc(strlen(buff)+1, sizeof(char));
	strcpy(F[i], buff);
	} 

char *S0;
fscanf(in,"%s",buff);
S0=(char *) calloc(strlen(buff)+1, sizeof(char));
strcpy(S0, buff);

fscanf(in,"%d",&P);
TR T[P];
for(i=0;i<P;i++)
	{
        fscanf(in,"%s",buff);
	T[i].current_state=(char *) calloc(strlen(buff)+1, sizeof(char));
	strcpy(T[i].current_state, buff);

        fscanf(in,"%s",buff);
	T[i].tape1_read_symbol=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape1_read_symbol, buff);

        fscanf(in,"%s",buff);
	T[i].tape2_read_symbol=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape2_read_symbol, buff);


        fscanf(in,"%s",buff);
	T[i].next_state=(char *) calloc(strlen(buff)+1,sizeof(char));
        strcpy(T[i].next_state, buff);


        fscanf(in,"%s",buff);
	T[i].tape1_write_symbol=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape1_write_symbol, buff);


        fscanf(in,"%s",buff);
	T[i].tape1_direction=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape1_direction, buff);

        fscanf(in,"%s",buff);
	T[i].tape2_write_symbol=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape2_write_symbol, buff);

        fscanf(in,"%s",buff);	
	T[i].tape2_direction=(char *) calloc(strlen(buff)+1, sizeof(char));
        strcpy(T[i].tape2_direction, buff);

	}



BAN a;

a.current_state=S0;
a.point1=1;
a.point2=1;
fscanf(in,"%s",a.input1);
fscanf(in,"%s",a.input2);
a.len1=strlen(a.input1);
a.len2=strlen(a.input2);

for(i=a.len1;i<MAX;i++)
	{
	a.input1[i]='#';
	}

for(i=a.len2;i<MAX;i++)
	{
	a.input2[i]='#';
	}

while( CHECK(a,M,F) ) {

i=TRANS(a,P,T);
if(i == -1)
	{
	fprintf(out,"The machine has blocked!");
	fprintf(out,"\n");
	return 0;
	}

a.current_state=T[i].next_state;
a.input1[a.point1]=T[i].tape1_write_symbol[0];
a.input2[a.point2]=T[i].tape2_write_symbol[0];

if(T[i].tape1_direction[0] == 'R')
	a.point1++;
if(T[i].tape1_direction[0] == 'L')
	a.point1--;

if(T[i].tape2_direction[0] == 'R') 
        a.point2++;
if(T[i].tape2_direction[0] == 'L')
        a.point2--;

if(a.point1 > a.len1)
	a.len1=a.point1;
if(a.point2 > a.len2)
	a.len2=a.point2;



}


for(i=0;i<=a.len1;i++)
	fprintf(out,"%c",a.input1[i]);

fprintf(out,"\n");

for(i=0;i<=a.len2;i++)
	fprintf(out,"%c", a.input2[i]);

fprintf(out,"\n");

	//ELIBERAREA MEMORIEI ALOCATE
free(S0);

for(i=0;i<P;i++)
	{
	free(T[i].current_state);
	free(T[i].tape1_read_symbol);
	free(T[i].tape2_read_symbol);
	free(T[i].next_state);
	free(T[i].tape1_write_symbol);
	free(T[i].tape1_direction);
	free(T[i].tape2_write_symbol);
	free(T[i].tape2_direction);
	}

for(i=0;i<M;i++)
        {
        free(F[i]);
	}

for(i=0;i<N;i++)
        {
        free(S[i]);
        }

fclose(in);
fclose(out);
return 0;
}


//VERIFICAREA STARII FINALE
int CHECK(BAN a, int N, char *F[N])
{
int i;
for(i=0;i<N;i++)
	{
	if(strcmp(a.current_state, F[i]) == 0)
	return 0;
	}
return 1;

}


//DETERMINAREA TRANZITIEI
int TRANS(BAN a, int P, TR T[P])
{
int i;
        for(i=0;i<P;i++){
                if(strcmp(T[i].current_state, a.current_state) == 0)
                if(T[i].tape1_read_symbol[0] ==  a.input1[a.point1])
                if(T[i].tape2_read_symbol[0] ==  a.input2[a.point2])
                        return i;
                }
return -1;
}
