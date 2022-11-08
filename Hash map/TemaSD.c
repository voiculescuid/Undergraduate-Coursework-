#include"antet.h"



//DECLARARE FUNCTII
unsigned int hash_f(const void *data, size_t len, size_t range);
TH* INIT(int BUCKET,TFHash fh,char*type,void AKeyN(FILE*,void*),void AKeyC(FILE*,void*),int compNUM(void*, void*),int compSTR(void*, void*),void FreeKEY1(void *x),void FreeKEY2(void *x));
void PRINT(FILE*out,TH*ah);
int InsLG(ALG aL, void* ae);
int InsTH(TH*a,void*i,char* type,int M);
info* CITIRE(FILE*in,char* type, void STUD(FILE*,void*), void MAT(FILE*,void*),void FreeMAT(void *),void FreeSTUD(void *));
void AStud(FILE*out,void *x);
void AMat(FILE*out,void *x);
void AKeyC(FILE*out,void *x);
void AKeyN(FILE*out,void *x);
int compNUM(void*x, void*y);
int compSTR(void*x, void*y);
void FIND(TH* ah, void *key,FILE*out);
int DELETE(TH* ah, void *key,char*type,int M);
void FreeMAT(void *x);
void FreeSTUD(void *x);
void FreeKEY1(void *x);
void FreeKEY2(void *x);
void DistrTH(TH** ah);
void DistrTH2(TH** ah);

int main()
{
TLG el,*p;
TH *h=NULL;
TH *h2=NULL;
char* type;
char* ins;
char up[20];
char *key1;
int key2;
type=malloc(2*sizeof(char));
float shot;
info *k;
int BUCKET, OP, COM=1,succ;
void *key;
int COUNT=0;
char input_filename[] = "input.in";
char output_filename[] = "output.out";
FILE *in = fopen(input_filename, "rt");
FILE *out = fopen(output_filename, "wt");

	while(COM)
		{
		fscanf(in,"%s",up);
		ins=strdup(up);
		if(strcmp(ins,"inithash") == 0)
		OP=1;
		if(strcmp(ins,"insert") == 0)
		OP=2;		
		if(strcmp(ins,"print") == 0)
		OP=5;
		if(strcmp(ins,"find") == 0)
		OP=3;
		if(strcmp(ins,"delete") == 0)
		OP=4;
		

		switch(OP)
			{

			case 1:
				{
				fscanf(in,"%s",type);
				fscanf(in,"%d",&BUCKET);
				fscanf(in,"%d",&COM);

				COM=COM+1;
				h= (TH*)INIT(BUCKET,hash_f,type,AKeyN,AKeyC,compNUM,compSTR,FreeKEY1,FreeKEY2);

				break;
				}

			case 2:
				{
				k=CITIRE(in,type, AStud, AMat,FreeMAT,FreeSTUD);
				succ=InsTH(h,k,type,BUCKET);
				COUNT=COUNT+succ;

				shot=(float)COUNT/BUCKET;
				if(shot>=0.75)
				{
				BUCKET=2*BUCKET;
				h2= (TH*)INIT(BUCKET,hash_f,type,AKeyN,AKeyC,compNUM,compSTR,FreeKEY1,FreeKEY2);
				
				for(p=h->v; p<h->v+h->size;p++)
					{
					for(el=*p;el!=NULL;el=el->urm)
						{
						if(el->info != NULL)
							{
							InsTH(h2,el->info,type,BUCKET);
							}
						}
					}

				}
				if(h2 != NULL)
					{
					DistrTH2(&h);
					h=h2;
					h2=NULL;
					}
				break;
				}
			case 3:
				{
				if(strcmp(type,"d")==0)
					{
					fscanf(in,"%d", &key2);
					key=malloc(sizeof(int));
					*((int*)key) = key2;
					}
				else 
					{
					fscanf(in,"%s", up);
					key1=strdup(up);
					key=malloc(strlen(key1)*sizeof(char));
					key=(char*)key1;
					}

				FIND(h, key,out);
				free(key);
				break;
				}

			case 4:
				{
				if(strcmp(type,"d")==0)
					{
					fscanf(in,"%d", &key2);
					key=malloc(sizeof(int));
					*((int*)key) = key2;
					}
				else 
					{
					fscanf(in,"%s", up);
					key1=strdup(up);
					key=malloc(strlen(key1)*sizeof(char));
					key=(char*)key1;
					}

				succ=DELETE(h,key,type,BUCKET);
				COUNT=COUNT-succ;
				free(key);
				break;
				}

			case 5:
				{
				PRINT(out,h);
				break;
				}
			}

		COM=COM-1;
		free(ins);
		}
fclose(in);
fclose(out);
DistrTH(&h);
free(type);
return 0;

}


