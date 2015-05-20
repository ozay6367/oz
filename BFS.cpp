#include<iostream>
#include<math.h>

#define MAX 100
using namespace std;

void BFS ( int P[] );
void input ( int, int, float P[][MAX] );
void selement ( float *, float *);
void srow ( int, int, int, float Q[][MAX] );
void cUtil(int P[], int Q[], int, int, int, int);
int fact(int);
void orow ( int, float, int, float, int, float P[][MAX] );
void ccol ( float P[][MAX], int Q[] );
void gauss ( int, float P[][MAX], float Q[] );

float P[MAX][MAX];
int n,m,f=0,h=0;
 
int main()
{
  int Q[MAX],i,dat[MAX];
  cout<<"\nEnter the no. of equations  : ";
  cin>>n;
  cout<<"Enter the no. of elements  :  ";
  cin>>m;

  input( n,m,P );
  
  for(i=0;i<m;i++)
    {
      Q[i]=i;
    }

  cUtil(Q,dat,0,m-1,0,(m-n));

  if(f==0)
    {
      cout<<"No BFS! \n";
    }

  cout<<"\nTotal No. of FS  :  "<<(fact(m)/(fact(m-n)*fact(n)))<<"\n\n";
  cout<<"\nTotal No. of BFS  :  "<<h<<"\n\n";
  
  return 0;
}

void BFS ( int col_no[] )
{
  float A[MAX][MAX];
  float x[MAX];
  if(m>n)
  {
    ccol(A,col_no);
    gauss( n,A,x );
  }

  else
  {
    gauss( n,P,x );
  }

  int i,j,k;
  j=0;k=0;
  int flag = 1;
  for(i=0;i<n;i++)
  {
    if(x[i]<0)
    {
      flag=-1;
      break;
    }
  }

  if(flag==1)
  {
    int l=0;
    cout<<"\nSolution no. "<<++h<<"   :  ";  
    f=1;
    for(i=0;i<m;i++)
    {
      if(m!=n && i==col_no[k])
      {
        cout<<"\nNon Basic = x"<<++l<<" , value = 0 ";
        k++;
        continue;
      }

      else
        cout<<"\nBasic = x"<<++l<<" , value = "<<x[j++];
    }
    cout<<endl<<endl;
  }
}

void input( int n, int m, float A[][MAX] )
{
  int i,j;
  
  for(i=0;i<n;i++)
    {
      cout<<"\nEnter for equation "<<i+1<<"  :  ";
      for(j=0;j<=m;j++)
	{
	  cin>>A[i][j];
	}
    }
}

void selement ( float *p, float *q )
{
  float temp;
  temp = *p;
  *p = *q;
  *q = temp;
}

void srow ( int n, int r1, int r2, float A[][MAX] )
{
  int i;
  for ( i=0; i<=n; i++ )
    selement ( &A[r1][i], &A[r2][i] );  
}

void cUtil(int arr[], int data[], int start, int end, int index, int r)
{
  if (index==r)
  {
    BFS ( data );
    return;
  }
 
  int i;
  for (i=start; i<=end && end-i+1 >= r-index; i++)
  {
    data[index] = arr[i];
    cUtil(arr, data, i+1, end, index+1, r);
  }
}

int fact(int n)
{
  int i,z=1;
  for(i=2;i<=n;i++)
    {
      z *= i;
    }
  return z;
}

void orow ( int n, float a, int r1, float b, int r2, float A[][MAX] )
{
  int i;
  
  for ( i=0; i<=n; i++ )
    A[r1][i] = (a*A[r1][i]) + (b*A[r2][i]);
  
}

void ccol ( float A[][MAX], int col_no[] )
{
  int i,c,j,col;
  c=0,col=0;
  int m_n = m-n;

  for(i=0;i<=m;i++)
  {
    if(c<m_n && col_no[c]==i)
    {
      c++;
      continue;
    }

    for(j=0;j<n;j++)
      A[j][col] = P[j][i];
    col++;
  }
}

void gauss( int n, float augA [][MAX], float x[] )
{
  int i,j,row_check;
  float a = 0.0, sum = 0.0;
  
  for ( i=0; i<n; i++ )
    {
      row_check = i;
      
      for ( j=i; j<n; j++ )
        {
	  if ( augA[j][i] != 0 )
            {
	      row_check = j;
	      break;
            }
        }
      
      srow ( n, i, row_check, augA );
      
      a = 1/augA[i][i];
      
      orow ( n, a, i, 0, i, augA );
      
      for ( j=i+1; j<n; j++ )
        { if(augA[j][i]!=0)
	    {
	      a = 1/augA[j][i];
	      
	      orow ( n, a, j, -1, i, augA );
	    }
        }
      
    }
  
  for ( i=(n-1); i>=0; i-- )
    {
      sum=0;
      for ( j=(i+1); j<n; j++ )
	sum+=augA[i][j]*x[j];
      
      x[i] = augA[i][n] - sum;
    }
  
  for(i=0;i<n;i++)
    {
      if(isnan(x[i]))
        x[i]=-9;
    }
}
