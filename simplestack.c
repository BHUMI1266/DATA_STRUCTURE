#include<stdio.h>
#include<stdlib.h>
#define size 5

//main
int main()
{
	int stack[size];
	int top =-1;
	int choice, value,popvalue;

	void push(int stack[], int *top, int value);
	int pop(int stack[], int *top);
	void peek(int stack[], int *top);
	void display(int stack[], int *top);

	while(1)
	{
		printf("\n==========Stack Menu============");
		printf("\n1.Push");
		printf("\n2.Pop");
		printf("\n3.Peek");
		printf("\n4.Display");
		printf("\n5.Exit");

		printf("\nEnter Your choice: ");
		scanf("%d",&choice);
//switch case
		switch(choice)
		{
		case 1:
			printf("\nEnter the value:");
			scanf("%d",&value);
			push(stack,&top,value);
			break;
		case 2:
			popvalue=pop(stack,&top);
			printf("\n Deleted value:%d", popvalue);
			break;
		case 3:
			peek(stack,&top);
			break;
		case 4:
			display(stack,&top);
			break;
		case 5:
			exit(0);
		default:
			printf("Invalid Choice.....");
			break;
		}
	}
	return 0;
}

//push function
void push(int stack[],int *top, int value)
{
	if(*top>= size-1)
	{
		printf("\nStack is Overflow");
	}
	else
	{
		*top = *top+1;
		stack[*top]=value;
		printf("\nValue Inserted successfully");
	}
}

//pop function
int pop(int stack[], int *top)
{
	int popvalue;
	if(*top==-1)
	{
		printf("\nStack is empty");
	}
	else
	{
		popvalue = stack[*top];
		*top = *top-1;
	}
	return popvalue;
}

//peek function
void peek(int stack[], int *top)
{
	if(*top==-1)
	{
			printf("\nStack is empty");
	}
	else
	{
		printf("\nTop Value is %d",stack[*top]);
	}
}

//display function
void display(int stack[], int *top)
{
	int i;
	if(*top==-1)
	{
		printf("\nStack is empty");
	}
	else
	{
		printf("\nStack elements:\n");
		for(i=0;i<=*top;i++)
		{
			printf("%d\n",stack[i]);
		}
	}
}