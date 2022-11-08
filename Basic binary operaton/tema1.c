#include<stdio.h>
#include<math.h>
int convert(int n);
int convert32(int n);
int add(int n);
int main(void)
{
int NR, COUNT, NUMAR=1;
//CITIRE
scanf("%d", &NR);
COUNT=NR;
	while(COUNT!=0)
	{
int i=0,IP11,IP12,IP13,IP14,IP1M,IP21,IP22,IP23,IP24,NUM, NET[255][5];	
scanf("%d.%d.%d.%d/%d", &IP11, &IP12, &IP13, &IP14, &IP1M);
scanf("%d.%d.%d.%d", &IP21, &IP22, &IP23, &IP24);
scanf("%d", &NUM);
	while(i!=NUM)
	{
	scanf("%d.%d.%d.%d/%d", &NET[i][1], &NET[i][2], &NET[i][3], &NET[i][4], &NET[i][5]);
	i++;
	}
printf("%d\n", NUMAR);
//TASK0	
printf("-0 ");
printf("%d.""%d.""%d.""%d\n",IP11,IP12,IP13,IP14);

//TASK1
int M[255],h=1,a=7,fr;
for(fr=1; fr<=255; fr++)
	{
	M[fr]=0;
	}
while(h<255)
{
	if(M[h]!=255 && IP1M!=0)
		{
		M[h]=M[h]+pow (2, a);
		a--;
		IP1M--;
		}
	else
	{
	a=7;
	h++;
	}
}
printf("-1 ");
printf("%d.%d.%d.%d\n", M[1], M[2], M[3], M[4]);

//TASK2
int B1,B2,B3,B4;
B1= (IP11 & M[1]);
B2= (IP12 & M[2]);
B3= (IP13 & M[3]);
B4= (IP14 & M[4]);
printf("-2 ");
printf("%d.%d.%d.%d\n", B1, B2, B3, B4);

//TASK3
unsigned char A1,A2,A3,A4;
A1= (IP11 | ~M[1]);
A2= (IP12 | ~M[2]);
A3= (IP13 | ~M[3]);
A4= (IP14 | ~M[4]);
printf("-3 ");
printf("%d.%d.%d.%d\n", A1, A2, A3, A4);

//TASK4
int OK;
printf("-4 ");
if((IP21 & M[1]) == B1 && (IP22 & M[2]) == B2 && (IP23 & M[3]) == B3 && (IP24 & M[4]) == B4) OK=1;
else OK=0; 
	if(OK==1) printf("da\n");
	else printf("nu\n");

//TASK5
printf("-5 ");
printf("%X.%X.%X.%X ", IP11, IP12, IP13, IP14);
printf("%o.%o.%o.%o\n", IP21, IP22, IP23, IP24);

//TASK6
printf("-6 ");

int NET2[255][4],IPNET[255][4], NET3[255][4],ab, ac,p=1, k ,d=7;
for(ab=1; ab<=255; ab++);
for(ac=1; ac<=4; ac++);
//{
//IPNET[ab][ac]=0;
//NET2[ab][ac]=0;
//NET3[ab][ac]=0;
//}
if(OK==1) printf("0");
else
{
	while(p<NUM)
	{
	k=1;
	while(k<=4)
		{
	        if(NET2[p][k]!=255 && NET[p][5]!=0)
	                {
	                NET2[p][k]=NET2[p][k]+pow (2, d);
	                d--;
	                NET[p][5]--;
	                }
	        else
	        {
	        d=7;
	        k++;
	        }
		}
                NET3[p][1]= (NET[p][1] & NET2[p][1]);
                NET3[p][2]= (NET[p][2] & NET2[p][2]);
                NET3[p][3]= (NET[p][3] & NET2[p][3]);
                NET3[p][4]= (NET[p][4] & NET2[p][4]);
                IPNET[p][1]= (IP21 & NET2[p][1]);
		IPNET[p][2]= (IP22 & NET2[p][2]);
		IPNET[p][3]= (IP23 & NET2[p][3]);
		IPNET[p][4]= (IP24 & NET2[p][4]);
		if(NET3[p][1] == IPNET[p][1] && NET3[p][2] == IPNET[p][2] && NET3[p][3] == IPNET[p][3] && NET3[p][4] == IPNET[p][4]) printf("%d ", p);

	p++;
	}
}
printf("\n");

//TASK7
printf("-7 ");
add(IP11); convert(IP11); printf("."); 
add(IP12); convert(IP12); printf(".");
add(IP13); convert(IP13); printf(".");
add(IP14); convert(IP14); printf(" ");
add(IP21); convert(IP21); printf(".");
add(IP22); convert(IP22); printf(".");
add(IP23); convert(IP23); printf(".");
add(IP24); convert(IP24);
printf("\n");

//TASK8
printf("-8 ");
convert32(IP11);printf(".");
convert32(IP12);printf(".");
convert32(IP13);printf(".");
convert32(IP14);
printf(" ");
convert32(IP21);printf(".");
convert32(IP22);printf(".");
convert32(IP23);printf(".");
convert32(IP24);
printf("\n");
	COUNT--;
	NUMAR++;
	}
return 0;
}
//////////////////////////////////////////////////////////////////////////

int convert32(int n)
{
int I1, I2;
I1=n/32;
switch(I1)
        {
        case 0:
        break;

        case 1:
        printf("1");
        break;

        case 2:
        printf("2");
        break;

        case 3:
        printf("3");
        break;
        
        case 4:
        printf("4");
        break;
        
        case 5:
        printf("5");
        break;

        case 6:
        printf("6");
        break;
        
        case 7:
        printf("7");
        break;
        }
I2=n%32;
switch(I2)
        {
        case 0:
	printf("0");
        break;

        case 1:
        printf("1");
        break;

        case 2:
        printf("2");
        break;

        case 3:
        printf("3");
        break;
        
        case 4:
        printf("4");
        break;
        
        case 5:
        printf("5");
        break;

        case 6:
        printf("6");
        break;
        
        case 7:
        printf("7");
        break;

        case 8:
        printf("8");
        break;

        case 9:
        printf("9");
        break;

        case 10:
        printf("A");  
        break;

        case 11:
        printf("B");
        break;

        case 12:
        printf("C");
        break;

        case 13:
        printf("D");
        break;

        case 14:
        printf("E");
        break;

        case 15:
        printf("F");
        break;

        case 16:
        printf("G");
        break;

        case 17:
        printf("H");
        break;

        case 18:
        printf("I");
        break;

        case 19:
        printf("J");
        break;

        case 20:
        printf("K");
        break;

        case 21:
        printf("L");
        break;

        case 22:
        printf("M");
        break;

        case 23:
        printf("N");
        break;

        case 24:
        printf("O");
        break;

        case 25:
        printf("P");
        break;

        case 26:
        printf("Q");
	break;

        case 27:
        printf("R");
        break;

        case 28:
        printf("S");
        break;

        case 29:
        printf("T");
        break;

        case 30:
        printf("U");
        break;

        case 31:
        printf("V");
        }
return 0;
}
/////////////////////////////////////////////////////////////////////
int convert(int n)
{
    int bin = 0,r, g = 1,ir;

    while (n!=0)
    {
        r = n%2;
        n /= 2;
        bin += r*g;
        g *= 10;
    }
    return printf("%d",bin);
}

int add(int n)
{
int OK;
	if(n<pow(2 , 8) && n>=pow(2 , 7)) OK=1;
	if(n<pow(2 , 7) && n>=pow(2 , 6)) OK=2;
	if(n<pow(2 , 6) && n>=pow(2 , 5)) OK=3;
	if(n<pow(2 , 5) && n>=pow(2 , 4)) OK=4;
	if(n<pow(2 , 4) && n>=pow(2 , 3)) OK=5;
	if(n<pow(2 , 3) && n>=pow(2 , 2)) OK=6;
	if(n<pow(2 , 2) && n>=pow(2 , 1)) OK=7;
	if(n<pow(2 , 1) && n>=pow(2 , 0)) OK=8;
	if(n == 0) OK =9;
	switch(OK)
	{
	case 1:
	break;

	case 2:
	printf("0");
	break;

	case 3:
	printf("00");
	break;

	case 4:
	printf("000");
	break;

        case 5:
	printf("0000");
        break;

        case 6:
        printf("00000");
        break;

        case 7:
        printf("000000");
        break;

        case 8:
        printf("0000000");
        break;

	case 9:
	printf("0000000");
	break;
	}
return 0;
}
