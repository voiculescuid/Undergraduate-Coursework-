#include"antet.h"


TH* INIT(int BUCKET,TFHash fh,char*type,void AKeyN(FILE*,void*),void AKeyC(FILE*,void*),int compNUM(void*, void*),int compSTR(void*, void*),void FreeKEY1(void *),void FreeKEY2(void *x))
{
	TH*h=(TH*)calloc(sizeof(TH),1);
	if (!h) 
	{	
		printf("Eroare alocare HASH TABLE.\n");
		return NULL;
	}
	h->v=(TLG*)calloc(BUCKET,sizeof(TLG));
	if(!h->v)
	{
		printf("Eroare alocare vector de pointeri TLG in HASH TABLE.\n");
		free(h);
		return NULL;
	}

	if(strcmp(type,"d")==0)
		{
		h->AKEY=AKeyN;
		h->comp=compNUM;
		h->FKEY=FreeKEY1;
		}
	else 
		{
		h->AKEY=AKeyC;
		h->comp=compSTR;
		h->FKEY=FreeKEY2;
		}

	h->size=BUCKET;
	h->fh=fh;
	return h;
}

void PRINT(FILE*out,TH*ah)

{
	TLG*p, el;
	for(p=ah->v; p<ah->v+ah->size;p++)
	{

			fprintf(out,"[%d] :",p-ah->v);
			for(el=*p;el!=NULL;el=el->urm)
				{
				fprintf(out," ");
				fprintf(out,"(");
				ah->AKEY(out,(char*)((info*)el->info)->key);
				fprintf(out," -> ");
				((info*)el->info)->AVAL(out,((info*)el->info)->val);
				fprintf(out,")");
				}
			fprintf(out,"\n");
	}

}


int InsLG(ALG aL, void* ae)
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

int InsTH(TH*a,void*i,char* type,int M)
{
int cod,rez,OK=0;
if(strcmp(type,"d") == 0)
	{
	cod=a->fh((int*)(((info*)i)->key),sizeof(int),M);
	}
else
	{
	cod=a->fh((char*)((info*)i)->key,strlen((char*)((info*)i)->key)*sizeof(char),M);
	}

	TLG el;
    for(el=a->v[cod];el!=NULL; el=el->urm)
	{
		if(a->comp(((info*)el->info)->key, ((info*)i)->key)==0)
		{
		((info*)el->info)->FVAL(((info*)(el->info))->val);
		a->FKEY(((info*)el->info)->key);
		free(el->info);

		el->info=i;
		OK=1;
		return 0;
		}	
	}
	
	if(OK == 0)
	rez=InsLG(a->v+cod,i); 
	
	return rez;	
}



info* CITIRE(FILE*in,char* type, void STUD(FILE*,void*), void MAT(FILE*,void*),void FreeMAT(void *),void FreeSTUD(void *))
{
info *i;
i=malloc(4*sizeof(void*));
char tip[5],up[30];
char *key1;
int key2;

TStudent st;
TMaterie mat;
			
	if(strcmp(type,"d")==0)
		{
		fscanf(in,"%d", &key2);
		i->key=malloc(sizeof(int));
		*((int*)i->key) = key2;
		}
	else 
		{
		fscanf(in,"%s", up);
		key1=strdup(up);
		i->key=(char*)key1;
		}



	fscanf(in,"%s",tip);
	if(strcmp(tip,"stud")==0)
		{
		fscanf(in,"%s",up);
		st.nume=strdup(up);
		fscanf(in,"%f",&st.medie);
		fscanf(in,"%s",st.grupa);
		fscanf(in,"%d",&st.varsta);

		i->val=malloc(sizeof(TStudent));
		*((TStudent*)i->val)=st;
		i->AVAL=STUD;
		i->FVAL=FreeSTUD;
		}

	else
		{
		fscanf(in,"%s",up);				
		mat.materie=strdup(up);
		
		fscanf(in,"%d",&mat.ore_curs);
		fscanf(in,"%d",&mat.ore_lab);
		fscanf(in,"%d",&mat.credit);
		fscanf(in,"%d",&mat.teme);
		
		i->val=malloc(sizeof(TMaterie));
		*((TMaterie*)i->val)=mat;
		i->AVAL=MAT;
		i->FVAL=FreeMAT;
		}
return i;

}

void AStud(FILE*out,void *x)
{
fprintf(out,"[Nume: %s, ", ((TStudent*)x)->nume);
fprintf(out,"Grupa: %s, ", ((TStudent*)x)->grupa);
fprintf(out,"Medie: %.2f, ", ((TStudent*)x)->medie);
fprintf(out,"Varsta: %d]", ((TStudent*)x)->varsta);
}

void AMat(FILE*out,void *x)
{
fprintf(out,"[Materie: %s, ", ((TMaterie*)x)->materie);
fprintf(out,"Ore_curs: %d, ", ((TMaterie*)x)->ore_curs);
fprintf(out,"Ore_lab: %d, ", ((TMaterie*)x)->ore_lab);
fprintf(out,"Credit: %d, ", ((TMaterie*)x)->credit);
fprintf(out,"Teme: %d]", ((TMaterie*)x)->teme);
}




void AKeyC(FILE*out,void *x)
{
fprintf(out,"%s", ((char*)x));
}

void AKeyN(FILE*out,void *x)
{
fprintf(out,"%d", *((int*)x));
}




int compSTR(void*x, void*y)
{
return strcmp((char*)x,(char*)y);
}

int compNUM(void*x, void*y)
{
if(*((int*)x) == *((int*)y))
	return 0;

else if(*((int*)x) > *((int*)y))
	return 1;

else
	return -1;
}




void FIND(TH* ah, void *key,FILE*out)
{
	TLG*p, el;
	int OK=0;
	for(p=ah->v; p<ah->v+ah->size;p++)
	{

			for(el=*p;el!=NULL;el=el->urm)
				{
				if(ah->comp(((info*)el->info)->key, key)==0)
					{
					((info*)el->info)->AVAL(out,((info*)el->info)->val);
					OK=1;
					}
				}
	}
	if(OK == 0)
	fprintf(out,"Nu exista");

	fprintf(out,"\n");

}

int DELETE(TH* ah, void *key,char*type,int M)
{
	int cod;

if(strcmp(type,"d") == 0)
	{
	cod=ah->fh(((int*)key),sizeof(int),M);
	}
else
	{
	cod=ah->fh((char*)key,strlen((char*)key)*sizeof(char),M);
	}
	
TLG*p=ah->v+cod, el,el2=NULL;

	for(el=*p;el!=NULL;el=el->urm)
		{
		if(ah->comp(((info*)el->info)->key, key)==0)
			{
			if(el2==NULL && el->urm ==NULL)
				{

				((info*)el->info)->FVAL(((info*)(el->info))->val);
				ah->FKEY(((info*)el->info)->key);
				free(el->info);
				free(el);

				*p=NULL;
				return 1;
				}
			if(el2==NULL && el->urm !=NULL)
				{
				*p=el->urm;
				((info*)el->info)->FVAL(((info*)(el->info))->val);
				ah->FKEY(((info*)el->info)->key);
				free(el->info);
				free(el);

				return 1;
				}
			if(el2!=NULL && el->urm==NULL)
				{
				el2->urm=NULL;
				((info*)el->info)->FVAL(((info*)(el->info))->val);
				ah->FKEY(((info*)el->info)->key);
				free(el->info);
				free(el);

				return 1;
				}
			if(el2!=NULL && el->urm !=NULL)
				{
				el2->urm=el->urm;

				((info*)el->info)->FVAL(((info*)(el->info))->val);
				ah->FKEY(((info*)el->info)->key);
				free(el->info);
				free(el);

				return 1;
				}
			}
		el2=el;	
		}

return 0;
}

void FreeSTUD(void *x)
{
free(((TStudent*)x)->nume);
free(x);
}

void FreeMAT(void *x)
{
free(((TMaterie*)x)->materie);
free(x);
}

void FreeKEY1(void *x)
{
free(x);
}

void FreeKEY2(void *x)
{
free(x);
}

void DistrTH(TH** ah)
{
	TLG*p,el,aux;

	for (p=(*ah)->v;p<(*ah)->v+(*ah)->size;p++)
	{
			for(el=*p;el!=NULL;)
			{
				aux=el;
				el=el->urm;
				((info*)aux->info)->FVAL(((info*)(aux->info))->val);
				(*ah)->FKEY(((info*)aux->info)->key);
				free(aux->info);
				free(aux);
			}	
			
	}
	free((*ah)->v);
	free(*ah);	
}

void DistrTH2(TH** ah)
{
	TLG*p,el,aux;

	for (p=(*ah)->v;p<(*ah)->v+(*ah)->size;p++)
	{
			for(el=*p;el!=NULL;)
			{
				aux=el;
				el=el->urm;

				free(aux);	
			}	
	
	}
	free((*ah)->v);
	free(*ah);		
}
