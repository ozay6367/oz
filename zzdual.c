#include<stdio.h>//11MA20025
float mod(float a)//mod function
{
float x=0;
if(a<0)
{
x=-a;
}
else
{
x=a;
}
return x;
}
int neg(float A[][10],int rows,int cols)//finding most negative element in rows
{
int i,f,pos1;
f=1000;
for(i=0;i<rows;i++)
{
if(A[i][cols]<f)
{
 f=A[i][cols];
pos1=i;
}
}
return pos1;
}
int pivo(float A[][10],int rows,int cols,int mne)//finding pivot in the most negative row
{
int i;
float r,lq,pos;
r=1000;
for(i=0;i<cols;i++)
{
lq=mod(A[rows][i]/A[mne][i]);
if((lq<r) && (A[mne][i]<0))
{
r=lq;
pos=i;
}
}
return pos;
}
int count(float A[][10],int rows,int cols)//checkpoint for the presence of any negative element
{
int count=0,i;
for(i=0;i<rows;i++)
{
if(A[i][cols]<0)
{
count=1;
}
break;
}
return count;
}
main()
{
int n,l,e,g,i,j,var,mne,c=1,pivot,k=0,k1=0,me[10],pi[10];
float A[10][10],nb[10],bv[10],max[10],C[10][10];
printf("enter no of variables\n");
scanf("%d",&var);
printf("enter no of constraints of less-equal sign\n");
scanf("%d",&l);
printf("enter no of constraints of equal sign\n");
scanf("%d",&e);
printf("enter no of constraints of greater sign\n");
scanf("%d",&g);
n=l+e+g;
printf("enter the coefficients with left hand side coeff:1st input greater than sign input then rest\n");
for(i=0;i<n;i++)
{
for(j=0;j<=var;j++)
{
scanf("%f",&A[i][j]);
}
}
printf("enter the max/min terms:if you want to input min then input it with -ve sign\n");
for(i=0;i<=var;i++)
{
scanf("%f",&max[i]);
}
for(i=0;i<n;i++)
{
nb[i]=0;
}
for(i=0;i<=var;i++)
{
if(max[i]<=0)
{
printf("%f\n",max[i]);
bv[i]=-max[i];
}
}
for(j=0;j<=var;j++)
{
A[n][j]=bv[j];
}
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
A[i][j]=-A[i][j];
}
}
printf("your matrix:\n");
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
printf("%f\t",A[i][j]);
}
printf("\n");
}
for(i=0;i<var;i++)
{
    pi[i]=0;
    me[i]=0;
}
do
{
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
C[i][j]=0;//inserting 0 in new matrix
}
}
c=count(A,n,var);
printf("c=%d\n",c);
mne=neg(A,n,var);
me[k1++]=mne;
printf("mne=%d\n",mne);
pivot=pivo(A,n,var,mne);
pi[k++]=pivot;
printf("pivot=%d\n",pivot);
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
if((i!=mne) || (j!=pivot))
{
C[i][j]=(A[i][j]*A[mne][pivot]-A[i][pivot]*A[mne][j])/A[mne][pivot];//inserting rest of the elements in the c array
}
}
}
for(i=0;i<=n;i++)//inserting elements in c array of pivot column
{
if(i!=mne)
{
 C[i][pivot]=A[i][pivot]*mod(1/A[mne][pivot]);
}
else
{
C[mne][pivot]=1/A[mne][pivot];
}
}
for(j=0;j<=var;j++)//inserting elements in c array of most negative row
{
if(j!=pivot)
{
C[mne][j]=A[mne][j]*(1/A[mne][pivot]);
}
else
{
C[mne][pivot]=1/A[mne][pivot];
}
}
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
A[i][j]=C[i][j];
}
}
printf("your matrix in computation stage\n");
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
printf("%f\t",C[i][j]);
}
printf("\n");
}
}while(c!=0);
printf("your matrix after computation:\n");
for(i=0;i<=n;i++)
{
for(j=0;j<=var;j++)
{
printf("%f\t",A[i][j]);
}
printf("\n");
}
printf("your optimum values is:%f\n",A[n][var]);
printf("your values of each variables:\n");
    for(i=k;i>0;i--)
    {
        if(pi[i]!=i)
        {
            printf("x%d=%f\n",pi[i]+2,A[me[i]][var]);
        }
        else
        {
            int t=0;
            printf("x%d=%d\n",pi[i]+2,t);
        }
    }
    int x1=0,x2=0;
    printf("x%d=%d\n",x1+1,x2);
}
