/* VOICULESCU Ion - 315CB */

#include"Head.h"


//COMPARARE

int compf(const void* a, const void* b)
{
	return ( ((info*)(a))->id - ((info*)(b))->id );
}


//INITIERE

TStiva* INITs()      
{ 
AS a = calloc(1,sizeof (TStiva));
		
  	a->vs = calloc(1,sizeof(TLG));     
  
 	return a;
}


//PUSH

int Push(ALG aL, void* ae)
{
  TLG aux = malloc(sizeof(TCelulaG));
	if(!aux) return 0;
	aux->info=(info*)ae;
	aux->urm = *aL;
	*aL = aux;
	return 1;
}

//POP

TCelulaG* Pop(AS S)
{
TLG*p=S->vs, el, el2,r;

	el=*p;
	if(el == NULL)
		return NULL;
	else
		{
		el2=el->urm;
		r=el;
		*p=el2;
		}

	return r;
}

//PRINTs


void PRINTs(AS S,FILE* outf)
{
AS as;
as=INITs();

TLG x;

x=Pop(S);
while (x != NULL)
	{
	Push(as->vs,x->info);
	free(x);
	x=Pop(S);
	}

fprintf(outf,"\"");
x=Pop(as);
while (x !=NULL)
	{
	Push(S->vs, x->info);
	fprintf(outf,"%s", ((info*)(x->info))->p);
	free(x);
	x=Pop(as);
	}
fprintf(outf,"\"\n");

free(as->vs);
free(as);

}

//SORTs
void SORTs(AS S)
{
int i=1,k=1;
TLG x;
info a[10000];
info* in;

x=Pop(S);
while (x != NULL)
	{
	a[i].id=((info*)(x->info))->id;
	a[i].p=((info*)(x->info))->p;
	i++;
	free(x);
	x=Pop(S);
	}

qsort(a,i,sizeof(info), compf);

for(k=1;k<i;k++)
	{
	in=calloc(1,sizeof(info));
	in->id=a[k].id;
	in->p=a[k].p;
	Push(S->vs, in);
	}

}

//CORRECTs

void CORRECTs(AS S,FILE* outf)
{
int len=0,max=0,div=0;	

TLG x,y,z;

AS SS,SSS;
SS=INITs();
SSS=INITs();

char* P1="[";
char* P2="(";
char* P3="{";

char* Q1="]";
char* Q2=")";
char* Q3="}";

x=Pop(S);
while (x != NULL)
	{
	Push(SSS->vs, x->info);
	free(x);
	x=Pop(S);
	}


x=Pop(SSS);
while(x != NULL)
	{
	Push(S->vs, x->info);

	if(strcmp(((info*)(x->info))->p,P1)==0 ||
	   strcmp(((info*)(x->info))->p,P2)==0 || 
	   strcmp(((info*)(x->info))->p,P3)==0 )
		Push(SS->vs, x->info);
	else
		{
		y=Pop(SS);
		if(y == NULL)
			{
			div=0;
			len=0;
			free(SS->vs);
			free(SS);
			SS=INITs();
			}

		else
			{
			
			if( (strcmp( ((info*)(y->info))->p, P1) == 0 && strcmp ( ((info*)(x->info))->p, Q1) == 0) ||
			    (strcmp( ((info*)(y->info))->p, P2) == 0 && strcmp ( ((info*)(x->info))->p, Q2) == 0) ||
			    (strcmp( ((info*)(y->info))->p, P3) == 0 && strcmp ( ((info*)(x->info))->p, Q3) == 0) )
				{
				z=Pop(SS);
				if(z == NULL)
					{
					len=len+div+2;

					if(len>max)
					max=len;

					div=0;
					}
				else
					{
					Push(SS->vs, z->info);
					free(z);
					div=div+2;
		
					if( div >= max)
					max=div;

					}
					
				}



			else
				{
				div=0;
				len=0;
				free(SS->vs);
				free(SS);
				SS=INITs();
				}
			}

		}
	free(x);
	x=Pop(SSS);
	}
free(SS->vs);
free(SS);

free(SSS->vs);
free(SSS);


fprintf(outf,"%d\n", max);
}

//FUNCTIE DE ELIBERARE

void DistrugeLG(ALG aL)
{ 
  TLG aux = *aL;  
  if (!aux) return;

  free(aux);  
}
