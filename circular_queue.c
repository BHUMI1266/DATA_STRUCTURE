#include<stdio.h>
#include<stdlib.h>
#define size 5

int cq[size];

void main()
{
	void insert(int *,int *,int val);
	int delet(int *,int *);
	void display(int *,int *);
	
	int ch,val,r;
	int *front,*rear;
	
	front=(int*)malloc(sizeof(int));
	rear=(int*)malloc(sizeof(int));

	*front=-1;
	*rear=-1;

	while(1)
	{
		printf("\n\n 1.insert\n 2.delete \n3.display \n 4.exit\n");
		printf("\n Enter choice:");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
				printf("Enter Your Element:");
				scanf("%d",&val);
				insert(front,rear,val);
				break;

			case 2:
				r=delet(front,rear);
				if(r!=-1)
				{
					printf("Removed value %d\n",r);
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
				//	break;
		}
	}
}

void insert(int *front,int *rear,int val)
{
	if((*front==0 && *rear==size-1) || (*rear +1) % size==*front)
	{
		printf("Circular queue is full\n");
	}
	else
	{
		if(*front ==-1 && *rear ==-1)
		{
			*front = *rear = 0;
		}
		else
		{
			*rear = (*rear + 1) % size;
		}
		cq[*rear]=val;
	}
}

int delet(int *front, int *rear)
{
	int r;
	if(*front == -1 && *rear ==-1)
	{
		printf("circular queue is empty \n");
		return -1;
	}
	r=cq[*front];

	if(*front ==*rear)
	{
		*front=*rear=-1;
	}
	else
	{
		*front=(*front+1)%size;
	}
	return r;
}
void display(int *front,int *rear)
{
	int i;

	if(*front == -1 && *rear == -1)
	{
		printf("circular queue is empty \n");
	}
	else
	{
		printf("\n Queue Element..");
		i=*front;
		while(1)
		{
			printf(" %d \n",cq[i]);
			if(i==*rear)
			{
				break;
			}
			i=(i+1) % size;
		}
		printf("\n");
	}
}