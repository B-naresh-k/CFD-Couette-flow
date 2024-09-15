#include <stdio.h>
#include <stdlib.h>
#include<math.h>
int main()
{
	int m = 100;  
	int i,j,l;
	double lhs, rhs[m], residual,t, dt= 0.01,temp;

	double u_old[m], u_new[m],gamma,error=1.0;
	
	gamma =  1.0;
	
	FILE  *file1, *file2;
    file1=fopen("log_iteration_vs_log_error.plt","w");
    file2=fopen("error1_vs_time1.dat","w");
        fprintf(file1, "Variables= \"X\",\"Y\"\n");
        fprintf(file1, "zone T= \"BLOCK1\", I=10, J=1\n\n");
	
	for(i = 0; i < m; i++)
	{
			if( i == (m-1) )
			{
				u_new[i] = 1.0; //tb
			}
		
			else if ( i == 0)
			{
				u_new[i] = 0.0; //bb
			}
			
			else
			{
				 u_new[i] = 0.0; 
			}			
	}
	
		for(i = 0; i < m; i++ )
	{
		
			printf(" %lf ", u_new[i]);
		
	}
	printf("\n");
	int iteration = 0;
	char name[50];

	while(t<500)
	{

		for(i = 0; i < m; i++)
		{
		
				u_old[i]= u_new[i]; 
				
		}
		
		for(i=0;i<m;i++)
		{
			
			if(i==m-2)
			{	
				rhs[i]=-u_new[i]-1.0;
			}
			else
			{
				rhs[i]=-u_new[i];
			}
		}
	
		for(j=0;j<m;j++)
		{
			lhs=0.0;
			if(j==0)
			{
				lhs=lhs+u_new[j+1];
			}
			
			else if(j==m-2)
			{
				lhs=lhs+u_new[j-1]-3.0*u_new[j];
		
			}
		
			else if (j==m-1)
			{
				lhs=lhs+u_new[j-1]-3.0*u_new[j];
			}
			else 
			{
				lhs=lhs+u_new[j-1]-(3.0)*u_new[j]+u_new[j+1];
			}
			
				residual=rhs[j]-lhs;
		
				if(j>=1 && j<=m-2)
				{
					temp=u_new[j];
					u_new[j]=u_new[j]+residual/(-3.0);
				}
			
			error=error+pow(u_new[j]-u_old[j],2);
		}
		
		error=sqrt(error/m);
		fprintf(file1,"%lf\t %lf\n",t,error);
		fprintf(file2,"%lf\t %lf\n",t, error);	
		t=t+dt;
		iteration++;
	}
	printf("\nerror=%lf\n",error);
		for(i = 0; i < m; i++ )
	{
		printf("%lf\n",u_new[i]);
	}
      printf("\n %d\t time=%lf",iteration,t);  
	
	
	return 0;
}

