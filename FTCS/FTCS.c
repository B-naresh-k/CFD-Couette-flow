#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int main()
{
	int m = 100,i,j;
	double dy;
	dy= 0.01;
	double error=1.0,t,q, dt= 0.005,u_old[m], u_new[m],gamma;
	gamma =   0.5;
	
	 FILE  *fp1, *file;
    fp1=fopen("log_iteration_vs_log_error.plt","w");
    file=fopen("error_vs_time.dat","w");
        fprintf(fp1, "Variables= \"X\",\"Y\"\n");
        fprintf(fp1, "zone T= \"BLOCK1\", I=10, J=1\n\n");
	
	for(i = 0; i < m; i++)
	{
			if( i == (m-1) )
			{
				u_new[i] = 1.0; 
			}
		
			else if ( i == 0)
			{
				u_new[i] = 0.0; 
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

	
	while(error>1e-6)
	{
		if((iteration+100)%100==0)
		{
			sprintf(name,"velocity_%.2f.dat",t);
			FILE *fp;
			fp=fopen(name,"w");
			for(i=0;i<m;i++)
			{
				fprintf(fp, "%lf\t%lf\n",u_new[i],i*.01);
			}
			fclose(fp);
		}
		
		for(i = 0; i < m; i++)
		{
			
				u_old[i]= u_new[i]; 
		}
		error = 0.0;
		for(i = 1; i < (m-1); i++)
		{
			
				u_new[i]= u_old[i]+gamma*(u_old[i+1]-2.0*u_old[i]+u_old[i-1]);
			    error=error + pow(u_new[i]-u_old[i],2);
		}
	
		error=sqrt(error/(m));
		iteration++;
	
		fprintf(fp1,"%lf\t %lf\n",t,error);
		fprintf(file,"%lf\t %lf\n",t,error);

			t=t+dt;
		
	}
	
		printf("\nvariation of velocity of flow with y at time t=50sec\n");
		for(i = m-1; i > -1; i-- )
	{
		
		printf("%lf\n",u_new[i]);
	}
      printf("\n\niteration(time=%lfs)= %d",t,iteration);  
	
	return 0;
}

