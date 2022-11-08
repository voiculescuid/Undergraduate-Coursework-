/* VOICULESCU Ion - 315CB */

#include"Head.h"

//INITIERE

TCoada* INITq()
{ 
	AQ a = calloc(1,sizeof (TCoada));  	

  	a->ic = calloc(1,sizeof(TLG)); 

  	return a;
}


//INTRq

int Intrq(ALG aL, void* ae)
{
  TLG aux = malloc(sizeof(TCelulaG));
  if(!aux) return 0;
  aux->info=(info*)ae;
  aux->urm = NULL;

TLG*p=aL, el;
	if(*p == NULL)
	{
	*aL=aux;
	}
	else
	{

for(el=*p;el->urm!=NULL;)
	{
	el=el->urm;
	}
	el->urm=aux;
	}
  return 1;
}

//EXTRq

TCelulaG* Extrq(AQ C)
{
TLG*p=C->ic, el=NULL, el2=NULL,r;

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

//PRINTq


void PRINTq(AQ C,FILE* outf)
{
AQ as;
as=INITq();

TLG x;

fprintf(outf,"\"");
x=Extrq(C);
while (x !=NULL)
	{
	Intrq(as->ic, x->info);
	fprintf(outf,"%s", ((info*)(x->info))->p);
	free(x);
	x=Extrq(C);
	}
fprintf(outf,"\"\n");

x=Extrq(as);
while (x != NULL)
	{
	Intrq(C->ic,x->info);
	free(x);
	x=Extrq(as);
	}

free(as->ic);
free(as);
}

//SORTq
void SORTq(AQ C)
{
int i=1,k;
TLG x;
info a[10000];
info* in;

x=Extrq(C);
while (x != NULL)
	{
	a[i].id=((info*)(x->info))->id;
	a[i].p=((info*)(x->info))->p;
	i++;
	free(x);
	x=Extrq(C);
	}

qsort(a,i,sizeof(info), compf);

for(k=1;k<i;k++)
	{
	in=calloc(1,sizeof(info));
	in->id=a[k].id;
	in->p=a[k].p;
	
	Intrq(C->ic, in);
	}
}



//CORRECTq

void CORRECTq(AQ C,FILE* outf)
{
TLG x;

AS SS,SSS;
SS=INITs();
SSS=INITs();

x=Extrq(C);
while (x != NULL)
	{
	Push(SS->vs, x->info);
	free(x);
	x=Extrq(C);
	}

CORRECTs(SS,outf);

x=Pop(SS);
while ( x != NULL)
	{
	Push(SSS->vs, x->info);
	free(x);
	x=Pop(SS);
	}

x=Pop(SSS);
while ( x != NULL)
	{
	Intrq(C->ic, x->info);
	free(x);
	x=Pop(SSS);
	}

free(SS->vs);
free(SS);

free(SSS->vs);
free(SSS);
}
