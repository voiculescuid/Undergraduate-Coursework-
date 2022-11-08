#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void print (int **a, int nl, int nc);
void freemat (int **a, int nl);
void fill(int **a,int nl, int nc,int cs, int ls, int rf, int gf, int bf);
int main()

{
int **a,**b;
int EPERM=1,EINVAL=2,ENOMEM=3;
int pls=0,ls,cs,rf,gf,bf,aux,ok,z,rot,nr,u,uu,nnl,nnc,nl,nc,i,j,op,c1,c2,l1,l2,x=0,y=0,rgb1,rgb2,rgb3,cc1,cc2,ll1,ll2;
//OPERATII
scanf("%d", &op);

while(op)        
{
switch(op)
	{
	


	case 1:
	if(pls!=0) freemat(a,nl);
        scanf("%d", &nc);
        scanf("%d", &nl);
        if(nl> 1024 || nc> 1024 || nl<1 || nc<1)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        exit(EXIT_FAILURE);
        }
        //ALOCARE
        a=malloc(nl*sizeof(int*));

        for(i=0;i<nl;i++)
                {
                a[i]=malloc(3*nc*sizeof(int*));
                }

        //CITIRE
        for(i=0;i<nl;i++)
                for(j=0;j<3*nc;j++)
                scanf("%d", &a[i][j]);
	pls++;
	break;
	
        





	case 2:
	//CROP
	scanf("%d", &c1);
	scanf("%d", &l1);
	scanf("%d", &c2);
	scanf("%d", &l2);

        if(l1<0 || l2<0 || l1>l2 || l1>nl || l2>nl|| c1<0 || c2<0 ||c1>c2 || c1>nc || c2>nc)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        freemat(a,nl);
        exit(EXIT_FAILURE);
        }


        //ALOCARE b
        b=malloc((l2-l1+1)*sizeof(int*));

        for(i=0;i<(l2-l1+1);i++)
                {
                b[i]=malloc(3*(c2-c1+1)*sizeof(int*));
                }

        //SCRIERE b
	x=0;
        for(i=l1;i<l2+1;i++)
        {        
	y=0;
		for(j=3*c1;j<3*(c2+1);j++)
                {
		b[x][y]=a[i][j];
		y++;
		}
	x++;
	}
	freemat(a,nl);

        //REALOCARE a
        a=malloc((l2-l1+1)*sizeof(int*));

        for(i=0;i<(l2-l1+1);i++)
                {
                a[i]=malloc(3*(c2-c1+1)*sizeof(int*));
                }
	//SCRIERE a
	for(i=0;i<(l2-l1+1);i++)
	{
		for(j=0;j<3*(c2-c1+1);j++)
		{
		a[i][j]=b[i][j];
		}
	}
	freemat(b,l2-l1+1);
	nl=l2-l1+1;
	nc=c2-c1+1;
	break;	

       	





	case 3:
	scanf("%d", &nnc);
	scanf("%d", &nnl);
        if(nnl> 1024 || nnc> 1024)
	{
	fflush(stdout);
	fprintf(stderr, "%d\n", EINVAL);
	freemat(a,nl);
	exit(EXIT_FAILURE);
	}
	//ALOCARE b
        b=malloc(nnl*sizeof(int*));

        for(i=0;i<nnl;i++)
                {
                b[i]=malloc(3*nnc*sizeof(int*));
                }
	//UMPLERE b
	for(i=0;i<nnl;i++)
	{
	for(j=0;j<3*nnc;j++)
		{
		b[i][j]=255;
		}
	}
	uu=0;
	u=0;
	while(u<nnl && u<nl)
	{
	uu=0;
		while(uu<3*nnc && uu<3*nc)
		{
		b[u][uu]=a[u][uu];
		uu++;
		}
	u++;
	}
	
	freemat(a,nl);

        //reALOCARE a
        a=malloc(nnl*sizeof(int*));

        for(i=0;i<nnl;i++)
                {
                a[i]=malloc(3*nnc*sizeof(int*));
                }
	//SCRIERE a
        for(i=0;i<nnl;i++)
        {
                for(j=0;j<3*nnc;j++)
                {
                a[i][j]=b[i][j];
                }
        }
        freemat(b,nnl);
        nl=nnl;
        nc=nnc;


	break;

        case 4:
	scanf("%d", &cc1);
	scanf("%d", &ll1);
	scanf("%d", &cc2);
	scanf("%d", &ll2);
	scanf("%d", &rgb1);
	scanf("%d", &rgb2);
	scanf("%d", &rgb3);

	if(ll1<0 || ll2<0 || ll1>ll2 || ll1>nl || ll2>nl|| cc1<0 || cc2<0 ||cc1>cc2 || cc1>nc || cc2>nc)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        freemat(a,nl);
        exit(EXIT_FAILURE);
        }

        //SCRIERE
	i=ll1;
	while(i<=ll2)
	{
	j=cc1;
		while(j<=cc2)
		{
                a[i][3*j]=rgb1;
         	a[i][(3*j)+1]=rgb2;
		a[i][(3*j)+2]=rgb3;
		j++;
		}
	i++;
        }       
    


        break;

        case 5:
	scanf("%d", &nr);
	if(nr<0 || nr>2000)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        freemat(a,nl);
        exit(EXIT_FAILURE);
        }

	while(nr)
	{
        //ALOCARE b
        b=malloc(nl*sizeof(int*));

        for(i=0;i<nl;i++)
                {
                b[i]=malloc(3*nc*sizeof(int*));
                }
        //SCRIERE b
        for(i=0;i<nl;i++)
        {
                for(j=0;j<3*nc;j++)
                {
                b[i][j]=a[i][j];
                }
        }

	a[0][0]=(b[1][0]+b[0][3])/2;
        a[0][1]=(b[1][1]+b[0][4])/2;
        a[0][2]=(b[1][2]+b[0][5])/2;

        a[nl-1][0]=(b[nl-2][0]+b[nl-1][3])/2;
        a[nl-1][1]=(b[nl-2][1]+b[nl-1][4])/2;
        a[nl-1][2]=(b[nl-2][2]+b[nl-1][5])/2;

        a[nl-1][3*(nc-1)]=(b[nl-2][3*(nc-1)]+b[nl-1][3*(nc-1)-3])/2;
        a[nl-1][3*(nc-1)+1]=(b[nl-2][3*(nc-1)+1]+b[nl-1][3*(nc-1)-2])/2;
        a[nl-1][3*(nc-1)+2]=(b[nl-2][3*(nc-1)+2]+b[nl-1][3*(nc-1)-1])/2;

        a[0][3*(nc-1)]=(b[1][3*(nc-1)]+b[0][3*(nc-1)-3])/2;
        a[0][3*(nc-1)+1]=(b[1][3*(nc-1)+1]+b[0][3*(nc-1)-2])/2;
        a[0][3*(nc-1)+2]=(b[1][3*(nc-1)+2]+b[0][3*(nc-1)-1])/2;
	
	//SCRIERE a
        for(i=1;i<nl-1;i++)
        {
                for(j=1;j<nc-1;j++)
                {
                a[i][3*j]=(b[i][3*j-3]+b[i][3*j+3]+b[i+1][3*j]+b[i-1][3*j])/4;
		a[i][3*j+1]=(b[i][3*j+4]+b[i][3*j-2]+b[i+1][3*j+1]+b[i-1][3*j+1])/4;
		a[i][3*j+2]=(b[i][3*j+5]+b[i][3*j-1]+b[i+1][3*j+2]+b[i-1][3*j+2])/4;
                }
        }
	
	for(i=1;i<nc-1;i++)
                {
                a[0][3*i]=(b[0][3*i-3]+b[0][3*i+3]+b[1][3*i])/3;
                a[0][3*i+1]=(b[0][3*i-2]+b[0][3*i+4]+b[1][3*i+1])/3;
                a[0][3*i+2]=(b[0][3*i-1]+b[0][3*i+5]+b[1][3*i+2])/3;

                a[nl-1][3*i]=(b[nl-1][3*i-3]+b[nl-1][3*i+3]+b[nl-2][3*i])/3;
                a[nl-1][3*i+1]=(b[nl-1][3*i-2]+b[nl-1][3*i+4]+b[nl-2][3*i+1])/3;
                a[nl-1][3*i+2]=(b[nl-1][3*i-1]+b[nl-1][3*i+5]+b[nl-2][3*i+2])/3;
                }
	
        for(i=1;i<nl-1;i++)
                {
                a[i][0]=(b[i-1][0]+b[i+1][0]+b[i][3])/3;
                a[i][1]=(b[i-1][1]+b[i+1][1]+b[i][4])/3;
                a[i][2]=(b[i-1][2]+b[i+1][2]+b[i][5])/3;

                a[i][3*(nc-1)]=(b[i-1][3*(nc-1)]+b[i+1][3*(nc-1)]+b[i][3*(nc-1)-3])/3;
                a[i][3*(nc-1)+1]=(b[i-1][3*(nc-1)+1]+b[i+1][3*(nc-1)+1]+b[i][3*(nc-1)-2])/3;
                a[i][3*(nc-1)+2]=(b[i-1][3*(nc-1)+2]+b[i+1][3*(nc-1)+2]+b[i][3*(nc-1)-1])/3;
                }
	nr--;
	freemat(b,nl);
	}
        break;




        case 6:
	scanf("%d", &rot);
        
	if(rot<0 || rot>3)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        freemat(a,nl);
        exit(EXIT_FAILURE);
        }


	while(rot)
	{
	//ALOCARE b
        b=malloc(nc*sizeof(int*));

        for(i=0;i<nc;i++)
                {
                b[i]=malloc(3*nl*sizeof(int*));
                }


	//SCRIERE b
	
	for(j=0;j<=nc-1;j++)
	{
	z=0;
	for(i=nl-1;i>=0;i--)
	{
	ok=0;
	while(ok<3)
		{
		b[j][z]=a[i][3*j+ok];
		ok++;
		z++;
		}
	}
	}
	freemat(a,nl);
		
	//ALOCARE a
        a=malloc(nc*sizeof(int*));

        for(i=0;i<nc;i++)
                {
                a[i]=malloc(3*nl*sizeof(int*));
                }

        //SCRIERE a
        for(i=0;i<nc;i++)
        {
                for(j=0;j<3*nl;j++)
                {
                a[i][j]=b[i][j];
                }
        }
	aux=nl;
	nl=nc;
	nc=aux;
	freemat(b,nl);
	rot--;
	}
        break;

        case 7:
	scanf("%d", &cs);
	scanf("%d", &ls);
	scanf("%d", &rf);
	scanf("%d", &gf);
	scanf("%d", &bf);
        
	if(ls<0 || ls>nl || cs<0 || cs>nc)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EINVAL);
        freemat(a,nl);
	exit(EXIT_FAILURE);
        }


	if(a[ls][cs] == rf && a[ls][cs+1] == gf && a[ls][cs+2] == bf) break;
	else fill(a,nl,nc,cs,ls,rf,gf,bf);	
        break;

	case 8:
	print(a, nl, nc);
	break;
	}
	scanf("%d", &op);
        if(op<0 || op>8)
        {
        fflush(stdout);
        fprintf(stderr, "%d\n", EPERM);
        exit(EXIT_FAILURE);
        }
	
}
freemat(a,nl);
}
//FUNCTIA FILL
void fill(int **a, int nl, int nc,int cs, int ls, int rf, int gf, int bf)
{
int ref1,ref2,ref3;

ref1=a[ls][3*cs];
ref2=a[ls][(3*cs)+1];
ref3=a[ls][(3*cs)+2];

a[ls][3*cs]=rf;
a[ls][(3*cs)+1]=gf;
a[ls][(3*cs)+2]=bf;

if(ls+1<nl && a[ls+1][3*cs]==ref1 && a[ls+1][(3*cs)+1]==ref2 && a[ls+1][(3*cs)+2]==ref3)
	fill(a,nl,nc,cs,ls+1,rf,gf,bf);

if(ls-1>=0 && a[ls-1][3*cs]==ref1 && a[ls-1][(3*cs)+1]==ref2 && a[ls-1][(3*cs)+2]==ref3)
        fill(a,nl,nc,cs,ls-1,rf,gf,bf);

if(cs+1<=nc && a[ls][3*(cs+1)]==ref1 && a[ls][3*(cs+1)+1]==ref2 && a[ls][3*(cs+1)+2]==ref3)
        fill(a,nl,nc,cs+1,ls,rf,gf,bf);

if(cs-1>=0 && a[ls][3*(cs-1)]==ref1 && a[ls][3*(cs-1)+1]==ref2 && a[ls][3*(cs-1)+2]==ref3)
        fill(a,nl,nc,cs-1,ls,rf,gf,bf);

}
//FUNTIA PRINT
void print(int **a, int nl, int nc)
{
int i,j;

printf("%d ", nc);
printf("%d", nl); 
printf("\n");

for(i=0;i<nl;i++)
	{
	for(j=0; j<3*nc; j++)
		{
		printf("%d ", a[i][j]);
		}
	printf("\n");
	}

}

//FUNCTIA FREE
void freemat(int **a, int nl)
{
int i;
for(i=0;i<nl;i++)
	free(a[i]);
free(a);
}
