#include<stdio.h>
#include<stdlib.h>

struct process
{
	char name[5];
	int bt;
	int at;
	int prt;
	int wt,ta;
	int flag;
};
typedef struct process processes;

void sort(processes temp[],int n) //sort the processes based on arrival time
{
	processes t;
	int i,j;
	for(i=1;i<n;i++)
		for(j=0;j<n-i;j++)
		{
			if(temp[j].at>temp[j+1].at)
			{
				t=temp[j];
				temp[j]=temp[j+1];
				temp[j+1]=t;
			}
		}
}

int accept(processes P[])
{
	int i,n;
	printf("\n Enter total no. of processes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\n PROCESS [%d]",i+1);
		printf(" Enter process name : ");
		scanf("%s",&P[i].name);
		printf(" Enter burst time : ");
		scanf("%d",&P[i].bt);
		printf(" Enter arrival time : ");
		scanf("%d",&P[i].at);
		printf(" Enter priority : ");
		scanf("%d",&P[i].prt);
	}
	printf("\n PROC.\tB.T.\tA.T.\tPRIORITY");
	for(i=0;i<n;i++)
		printf("\n %s\t%d\t%d\t%d",P[i].name,P[i].bt,P[i].at,P[i].prt);
	return n;
}

// FCFS Algorithm
void FCFS(processes P[],int n)
{
	processes temp[10];
	int i,j,sumw=0,sumt=0,x=0;
	float avgwt=0.0,avgta=0.0;
	for(i=0;i<n;i++)
		temp[i]=P[i];

	sort(temp,n);	//arrival time sorting

		printf("\n\n PROC.\tB.T.\tA.T.");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at);

		sumw=temp[0].wt=0;
		sumt=temp[0].ta=temp[0].bt-temp[0].at;

		for(i=1;i<n;i++)
		{
			temp[i].wt =(temp[i-1].bt+temp[i-1].at+temp[i-1].wt)-temp[i].at;
			temp[i].ta=(temp[i].wt+temp[i].bt);
			sumw=sumw+temp[i].wt;
			sumt=sumw+temp[i].ta;
		}
		avgwt=(float)sumw/n;
		avgta=(float)sumt/n;
		printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at,temp[i].wt,temp[i].ta);
		
		printf("\n\n GANTT CHART\n ");
		for(i=0;i<n;i++)
			printf("   %s   ",temp[i].name);
		printf("\n ");

		printf("0\t");
		for(i=0;i<n;i++)
		{
			x=x+temp[i].bt;
			printf("%d      ",x);
		}
		printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}



//SJF Non Pre-emptive
void SJF_NP(processes P[],int n)
{
	processes temp[10];
	processes t;
	int i,j,sumw=0,sumt=0,x=0;
	float avgwt=0.0,avgta=0.0;

	for(i=0;i<n;i++)
		temp[i]=P[i];

	sort(temp,n);	//arrival time sorting

	for(i=2;i<n;i++)	//sorting the processes based on busrt time since it is SJF
		for(j=1;j<n-i+1;j++)
		{
			if(temp[j].bt>temp[j+1].bt)
			{
				t=temp[j];
				temp[j]=temp[j+1];
				temp[j+1]=t;
			}
		}

	printf("\n\n PROC.\tB.T.\tA.T.");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at);

		sumw=temp[0].wt=0;
		sumt=temp[0].ta=temp[0].bt-temp[0].at;

		for(i=1;i<n;i++)
		{
			temp[i].wt=(temp[i-1].bt+temp[i-1].at+temp[i-1].wt)-temp[i].at;
			temp[i].ta = (temp[i].wt+temp[i].bt);
			sumw=sumw+temp[i].wt;
			sumt=sumt+temp[i].ta;
		}
		avgwt=(float)sumw/n;
		avgta=(float)sumt/n;
		printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at,temp[i].wt,temp[i].ta);
		
		printf("\n\n GANTT CHART\n ");
		for(i=0;i<n;i++)
			printf("   %s   ",temp[i].name);
		printf("\n ");

		printf("0\t");
		for(i=0;i<n;i++)
		{
			x=x+temp[i].bt;
			printf("%d      ",x);
		}
		printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}

//Priority Non Pre-emptive
void PRT_NP(processes P[],int n)
{
	processes temp[10];
	processes t;
	int sumw=0,sumt=0,i,j,x=0;
	float avgwt=0.0,avgta=0.0;

	for(i=0;i<n;i++)
		temp[i]=P[i];

	sort(temp,n);	// Arrival time sorting

	for(i=2;i<n;i++)	//sort processes based on priority
		for(j=1;j<n-i+1;j++)
		{
			if(temp[j].prt>temp[j+1].prt)
			{
				t=temp[j];
				temp[j]=temp[j+1];
				temp[j+1]=t;
			}
		}

	printf("\n\n PROC.\tB.T.\tA.T.");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at);

		sumw=temp[0].wt=0;
		sumt=temp[0].ta=temp[0].bt-temp[0].at;

		for(i=1;i<n;i++)
		{
			temp[i].wt=(temp[i-1].bt+temp[i-1].at+temp[i-1].wt)-temp[i].at;
			temp[i].ta=(temp[i].wt+temp[i].bt);
			sumw=sumw+temp[i].wt;
			sumt=sumt+temp[i].ta;
		}
		avgwt=(float)sumw/n;
		avgta=(float)sumt/n;
		printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
		for(i=0;i<n;i++)
			printf("\n %s\t%d\t%d\t%d\t%d",temp[i].name,temp[i].bt,temp[i].at,temp[i].wt,temp[i].ta);
		
		printf("\n\n GANTT CHART\n ");
		for(i=0;i<n;i++)
			printf("   %s   ",temp[i].name);
		printf("\n ");

		printf("0\t");
		for(i=0;i<n;i++)
		{
			x=x+temp[i].bt;
			printf("%d      ",x);
		}
		printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}


int main()
{
	
	processes P[10];
	int ch,n;
	do{
		printf("\n\n CPU SCHEDULING ALGORITHMS\n");
		printf("\n 1. Enter process data.");
		printf("\n 2. FCFS");
		printf("\n 3. SJF (Non Pre-emptive)");
		printf("\n 4. Priority Scheduling (Non Pre-emptive)");
		printf("\n 5. Exit\n Select : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:n=accept(P);
				   break;
			case 2:FCFS(P,n);
				   break;
			case 3:SJF_NP(P,n);
				   break;
			case 4:PRT_NP(P,n);
				   break;
			case 5:exit(0);
				   break;
			default:printf("Invalid Input");			
		}
	}while(ch != 5);
	getch();
	return 0;
}
