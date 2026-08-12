
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define size 5

int q[size];

void main()
{

	int *front,*rear;
	int choice,val,r;

	void insert(int *,int *,int val);
	int delet(int *,int *);
	void display(int *,int *);

	 
	front=(int *)malloc(sizeof(int));
	 rear=(int *)malloc(sizeof(int));

	*front=*rear=-1;

	while(choice!=4)
	{
		printf("\n ---------------select your Queue Operation------------\n");
		printf("\n 1.Insert \n 2.Delete \n 3.Display\n  4.exit\n\n ");
		printf("Enter Your Choice:");
		scanf("%d",&choice);

		switch(choice)
		{
				
			case 1:
					printf("Enter Queue Element:");
					scanf("%d",&val);
					insert(front,rear,val);
					break;
			case 2:
					if( (*rear)==-1&&(*front)==-1 )
					{
						printf("\n queue is empty");
					}
					else
					{
						r=delet(front,rear);
						printf("\n Deleted Element Is : %d ",r);
					}
					break;
			
			case 3:
					display(front,rear);
					break;
			case 4:
					exit(0);
					break;

			default:
				printf("\n invalid choice");
				break;
		}

	}
}
void insert(int *front,int *rear,int value)
{
	if((*front)==-1 && (*rear)==-1)
	{
			(*front)=(*rear)=0;
			q[(*rear)]=value;
	}
	else
	{
		if((*rear)==size-1)
		{
			printf(" \n Queue is full");
			
		}
		else
		{
			(*rear)=(*rear)+1;
			q[(*rear)]=value;
		}
	}
}
int delet(int *front,int *rear)
{
	int rval;

	if( (*rear)==-1&&(*front)==-1 )
	{
		printf("\n queue is empty");
	}
	else
	{
		if((*front)==(*rear))
		{
			rval=q[(*front)];
			(*front)=(*rear)=-1;
		}
		else
		{
			rval=q[(*front)];
			(*front)=(*front)+1;
		}
	}
		return rval;
}

void display(int *front,int *rear)
{
	int i;

	if((*front)==-1 && (*rear)==-1)
	{
		printf("\n queue is empty");
	}
	else
	{
		for(i=(*front);i<=(*rear);i++)
		{
			printf("%d \n",q[i]);
		}
	}
}

