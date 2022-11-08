#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"lista.h"
#include"student.h"
#include"materie.h"

typedef unsigned int (*TFHash)(const void *data, size_t len, size_t range);

typedef struct {
	void *val;
	void *key;
	void (*AVAL)(FILE*,void *);
	void (*FVAL)(void *);
} info;


typedef struct {
	int size;	
	TFHash fh;
	TLG *v;
	int (*comp)(void*, void*);
	void (*AKEY)(FILE*,void *);
	void (*FKEY)(void*);
} TH;



