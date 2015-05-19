#include<iostream>
using namespace std;
void partition(int *,int,int);
void swap(int *,int *);
void partition(int *A,int p,int r)
{
    int i=0,x,j=0;
    x=A[p];
    i=p+1;
    j=r;
    if(i>=j)
        return;
    while(i<j)
    {
        while(A[j]>=x && (j>p))
        {
            j--;
        }
        while(A[i]<=x && (i<r))
        {
            i++;
        }
    if(i<j)
    {
        swap(&A[j],&A[i]);
    }
}
if(i==p+1)
{
    partition(A,p+1,r);
}
if(j==r)
{
    swap(&A[p],&A[j]);
    partition(A,p,r-1);
}
else
{
    swap(&A[p],&A[j]);
    partition(A,p,j-1);
    partition(A,j+1,r);
}
}
void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int check(float A[][10],int rows,int col)
{
    int count=0,i,j;
    for(i=0;i<col;i++)
    {
        if(A[rows][i]<0)
        {
            count=count+1;
        }
    }
    cout<<count;
    return count;
}
int min_coeff(float A[][10],int rows,int col,int p)//returning the pos of min coeff of rows
{
    int pos_r,i,j;
    float cal,cal1;
    cal=A[0][col]/A[0][p];
    for(i=1;i<rows;i++)
    {
        cal1=A[i][col]/A[i][p];
        if(cal1<cal)
        {
            cal=cal1;
            pos_r=i;
        }
    }
    return pos_r;
}
int search_mne(float A[][10],int rows,int col)//returning the pos of most negative element of column
{
    int i,j,pos_col;
    float s;
    s=A[rows][0];
    for(i=1;i<col;i++)
    {
        if(A[rows][i]<s)
        {
            s=A[rows][i];
            pos_col=i;
        }
    }
    return pos_col;
}
main()
{
    int n,m,i,j,k=0,neg_col,min_row,n_col[10],m_row[10],o=0;//p=neg_col;r=min_row;
    float b[10],m1[10],A[10][10],C[10][10];
    cout<<"enter no of variables you want to enter\n";
    cin>>n;
    cout<<"enter no of equations you want to enter\n";
    cin>>m;
    cout<<"enter the coefficients of m equations\n";
    for(i=0;i<m;i++)//equations representing rows
    {
        for(j=0;j<n;j++)//variables coeff representing column
        {
            cin>>A[i][j];//ex-row-1: no of columns
        }
    }
    cout<<"enter the  R.H.S coefficients of m equations\n";
    for(i=0;i<m;i++)
    {
        cin>>b[i];
    }
    cout<<"enter the coefficients of maximization terms with R.H.S term\n";
    for(i=0;i<=n;i++)
    {
        cin>>m1[i];
    }
    for(i=0;i<m;i++)
    {
        A[i][n]=b[i];
    }
    for(j=0;j<=n;j++)
    {
        if(j!=n)
            {
                    A[m][j]=-m1[j];
            }
            else
            {
                A[m][j]=m1[j];
            }
    }
    cout<<"your required agumented matrix\n";
    for(i=0;i<=m;i++)//no of equations->rows
    {
        for(j=0;j<=n;j++)//no of variables->columnds
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            C[i][j]=0;
        }
    }
   while(check(A,m,n)!=0)
    {
         neg_col=search_mne(A,m,n);
         cout<<neg_col<<endl;
    min_row=min_coeff(A,m,n,neg_col);
    cout<<min_row<<endl;
    n_col[k++]=neg_col;
    m_row[o++]=min_row;
         for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            if(i!=min_row || j!=neg_col)
            {
                C[i][j]=(A[i][j]*A[min_row][neg_col]-A[i][neg_col]*A[min_row][j])/A[min_row][neg_col];
            }
        }
    }
            for(j=0;j<=n;j++)
            {
                C[min_row][j]=A[min_row][j]/A[min_row][neg_col];
            }
        for(i=0;i<=m;i++)
            {
                if(i!=min_row)
                {
                    C[i][neg_col]=-A[i][neg_col]/A[min_row][neg_col];
                }
                else
                {
                    C[i][neg_col]=A[i][neg_col]/A[min_row][neg_col];
                }
            }
            cout<<"\nyour matrix in computation stage\n";
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            cout<<C[i][j]<<"\t";
        }
        cout<<endl;
    }
     for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            A[i][j]=C[i][j];
    }
    }
    }
    cout<<"your matrix after computation\n";
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
     partition(m_row,0,k-1);
    cout<<"your max value is: "<<A[m][n]<<endl;
    cout<<"your variables values are: ";
    for(i=k-1;i>=0;i--)
    {
        cout<<A[m_row[i]][n]<<"\t";
    }
    cout<<endl;
}
