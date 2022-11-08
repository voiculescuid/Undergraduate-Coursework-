/* VOICULESCU Ion - 315CB */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//LISTA GENERICA SIMPLU INLANTUITA.

typedef struct celulag
	{ 
 	void* info;           
  	struct celulag *urm;   
	} TCelulaG, *TLG, **ALG; 


//STRUCTURA DE TIP COADA

typedef struct
	{ 
	TLG 	*ic; 			
	} TCoada, *AQ;


//STRUCTURA DE TIP STIVA

typedef struct
	{ 
	TLG	*vs;
	} TStiva, *AS;


//STRUCTURA PENTRU INFORMATIE

typedef struct
	{
	int id;
	char *p;
	} info;

//DECLARARE FUNCTII
TStiva* INITs();
TCoada* INITq();
int Push(ALG aL, void* ae);
TCelulaG* Pop(AS S);
void PRINTs(AS S,FILE* outf);
int Intrq(ALG aL, void* ae);
TCelulaG* Extrq(AQ C);
void PRINTq(AQ C, FILE* outf);
void SORTs(AS S);
void SORTq(AQ C);
void CORRECTs(AS S,FILE* outf);
void CORRECTq(AQ C, FILE* outf);
int compf(const void* a, const void* b);
void DistrugeLG(ALG aL);

