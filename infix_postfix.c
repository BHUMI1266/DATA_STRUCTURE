#include<stdio.h>


int priority(char ch)   // check the priority
{
	//if(ch=='(' || ch==')')
		//return 3;
	
	
	
	if(ch=='*' || ch=='/')
		return 2;
	else if(ch=='+' || ch=='-')
		return 1;
	else
		return 0;
}

int push(char stack[], int top, char ch)   //insert the character in stack
{
	if(top==9)
		printf("\n Stack is overflow");
	else
	{
		top++;
		stack[top]=ch;
	}
	return top;
}

int pop(char stack[], int top)  //the character out of the stack
{
	if(top==-1)
		printf("\nStack is underflow");
	else
	{
		if(stack[top]!='(')
		{
			printf("%c",stack[top]);
		}
		top--;		
	}
	return top;
}

//infix to postfix

void converter (char in[],char stack[],int top)  //convert 
{
	int i=0;
	while(in[i]!='\0')          // for end of expression that element are checked
	{
		if(in[i]=='+' || in[i]=='-' ||
			in[i]=='*' || in[i]=='/' ||
			in [i]=='(' || in[i]==')')
		{
			if(top==-1 || in[i]=='(')
			{
				top=push(stack,top,in[i]);
			}
			else if(in[i]==')')
			{
				while(stack[top]!='(')
				{
					top = pop(stack,top);
				}
				top--;
				
			}
			else
			{
				while(top!=-1 && priority(stack[top])>=priority(in[i])) //to check priority of operand
				{
				
					top=pop(stack,top);
					//printf("%c", stack[top]);
				}
				top=push(stack,top,in[i]);
			}
		}
		else
		{
			printf("%c",in[i]); // opreand directly print
		}
		i++;
	}
	while(top!=-1)
	{
		top=pop(stack,top);
	}
}
int main()
{
	char stack[10],in[50];
	int top=-1;

	printf("\nEnter infix expression: ");
	scanf("%s",in);
	printf("\n Postfix expression: ");
	
	converter(in,stack,top);

	return 0;
}