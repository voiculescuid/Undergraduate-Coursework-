/* VOICULESCU Ion - 315CB */

#include"Head.h"

int main(int argc, char *argv[])
{

FILE* inf = fopen(argv[1], "rt");
FILE* outf = fopen(argv[2], "wt");

int OP,S,C,CO,ido,i;
char *ins;
char up[30];
info* in=NULL;
TLG x;

fscanf(inf,"%d", &OP);
fscanf(inf,"%d", &S);
fscanf(inf,"%d", &C);

AQ CC[C];
AS SS[S];


for(i=0;i<C;i++)
	CC[i]=INITq();

for(i=0;i<S;i++)
	SS[i]=INITs();


while(OP)
	{

		fscanf(inf,"%s",up);
		ins=strdup(up);

		if(strcmp(ins,"push") == 0)
		CO=1;
		if(strcmp(ins,"pop") == 0)
		CO=2;		
		if(strcmp(ins,"sorts") == 0)
		CO=3;
		if(strcmp(ins,"prints") == 0)
		CO=4;
		if(strcmp(ins,"corrects") == 0)
		CO=5;
		if(strcmp(ins,"intrq") == 0)
		CO=6;
		if(strcmp(ins,"extrq") == 0)
		CO=7;		
		if(strcmp(ins,"sortq") == 0)
		CO=8;
		if(strcmp(ins,"printq") == 0)
		CO=9;
		if(strcmp(ins,"correctq") == 0)
		CO=10;
		free(ins);



		switch(CO)
			{

			case 1:
				fscanf(inf,"%d", &ido);

				in=calloc(1,sizeof(info));
				fscanf(inf,"%d", &in->id);
				in->p=calloc(2,sizeof(char));
				fscanf(inf,"%s", in->p);
	
				Push(SS[ido]->vs, in);
			break;
	


			case 2:
				fscanf(inf,"%d", &ido);
				x=Pop(SS[ido]);
				if(x != NULL)
				DistrugeLG(&x);
			break;


	
			case 3:
				fscanf(inf,"%d", &ido);
				SORTs(SS[ido]);
			break;
	
			case 4:
				for(i=0; i<S; i++)
				PRINTs(SS[i],outf);
			break;


	
			case 5:
				fscanf(inf,"%d", &ido);
				CORRECTs(SS[ido],outf);
			break;
	


			case 6:
				fscanf(inf,"%d", &ido);

				in=calloc(1,sizeof(info));
				fscanf(inf,"%d", &in->id);
				in->p=calloc(2,sizeof(char));
				fscanf(inf,"%s", in->p);
	
				Intrq(CC[ido]->ic, in);
			break;


	
			case 7:
				fscanf(inf,"%d", &ido);
				x=Extrq(CC[ido]);
				if(x != NULL)
				DistrugeLG(&x);
			break;


	
			case 8:
				fscanf(inf,"%d", &ido);
				SORTq(CC[ido]);
			break;


	
			case 9:
				for(i=0; i<C; i++)
				PRINTq(CC[i],outf);
			break;


	
			case 10:
				fscanf(inf,"%d", &ido);
				CORRECTq(CC[ido],outf);
			break;
			}
	OP--;
	}

free(in);

for(i=0;i<C;i++)
	{
	x=Extrq(CC[i]);
	while ( x != NULL)
		{
		DistrugeLG(&x);
		x=Extrq(CC[i]);
		}
	free(CC[i]->ic);
	free(CC[i]);
	}

for(i=0;i<S;i++)
	{
	x=Pop(SS[i]);
	while ( x != NULL)
		{
		DistrugeLG(&x);
		x=Pop(SS[i]);
		}
	free(SS[i]->vs);
	free(SS[i]);
	}

fclose(outf);
fclose(inf);

return 0;
}
