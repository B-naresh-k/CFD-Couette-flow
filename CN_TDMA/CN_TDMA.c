#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int main()
{
	int m = 100,i,j; 
	double t, dt= 0.01,u_old[m], u_new[m] ,temp, gamma,error=1;
	gamma =1.0;
	double ai, bi, ci, d[m-2], p[m-2], q[m-2];
	
	ai=2; bi=-0.5; ci=-0.5;
	
	FILE  *file1, *file2;
    file1=fopen("log_iteration_vs_log_error.plt","w");
    file2=fopen("error1_vs_time1.dat","w");
        fprintf(file1, "Variables= \"X\",\"Y\"\n");
        fprintf(file1, "zone T= \"BLOCK1\", I=10, J=1\n\n");
	
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
		
		d[0]=(0.5*u_new[1]);
		p[0]=1/4;
		q[0]=d[0]/2;
	
		for(i=1;i<m-1;i++)
		{
			d[i]=(0.5*u_new[i+1]+0.5*u_new[i-1]);
			p[i]=0.5/(2-0.5*p[i-1]);
			q[i]=(d[i]+0.5*q[i-1])/(2-0.5*p[i-1]);
			
		}
		error=0.0;
		
		for(i = m-2 ; i > 0; i--)
		{
			
				temp=u_new[i];
				u_new[i]=p[i]*u_new[i+1]+q[i];
					error=error+ pow(u_new[i]-temp,2);					
		}
		
		error=sqrt(error/m);
		fprintf(file1,"%lf\t %lf\n",t,error);
		fprintf(file2,"%lf\t %lf\n",t, error);		
					
		t=t+dt;
		
		printf("time=%lf\t error=%lf\n",t, error);
		iteration++;
	}
	
		for(i = 0; i < m; i++ )
	{	
		printf("%lf\n",u_new[i]);
	}
       printf("\n %d\t time=%lf",iteration,t); 
	
	return 0;
}

