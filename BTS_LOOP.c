#include<stdio.h>
#include<stdlib.h>

struct std
{
	int ro;
	struct std *lptr;
	struct std *rptr;
};

struct std *root=NULL;
void insert(int n)
{
	struct std * next;
	struct std * tmp,*prev;
	if(root==NULL)
	{
		root=(struct std*)malloc(sizeof(struct std));
		root->ro=n;
		root->lptr=NULL;
		root->rptr=NULL;
	}
	else
	{
		tmp=root;
		
		do{
			prev=tmp;
			if(tmp->ro > n)
				tmp=tmp->lptr;
			else
				tmp=tmp->rptr;
		}
		while(tmp !=NULL);

		next=(struct std*)malloc(sizeof(struct std));
		next->ro=n;
		next->lptr=NULL;
		next->rptr=NULL;
		if(prev->ro > n)
			prev->lptr=next;
		else
			prev->rptr=next;
	}
}
void display(struct std *root)
{
	struct std *tmp;
	tmp = root;
	if(tmp!=NULL)
	{
		display(tmp->lptr);
		printf(" %d ",tmp->ro);
		display(tmp->rptr);
	}
}
void delet(struct std *root,int n)
{
	int f=0,x,y;
	struct std *tmp,*prev;
	tmp=root;
	
	do{
		if(tmp->ro == n)
		{
			f=1;
			break;
		}
		else if(tmp->ro > n)
		{
			prev=tmp;
			tmp=tmp->lptr;
		}
		else
		{
			prev=tmp;
			tmp=tmp->rptr;
		}
	}while(tmp != NULL);

	if(f==0)
	{
		printf("\n Number is not found ");
	}
	else
	{
		if(tmp->lptr==NULL && tmp->rptr==NULL)
		{
			if(prev->ro > n)
				prev->lptr=NULL;
			else
				prev->rptr=NULL;
			free(tmp);
		}
		else if(tmp->lptr==NULL || tmp->rptr==NULL)
		{
			if(tmp->rptr==NULL)
			{
				if(prev->ro > n)
					prev->lptr=tmp->lptr;
				else
					prev->rptr=tmp->lptr;
			}
			else
			{
				if(prev->ro > n)
					prev->lptr=tmp->rptr;
				else
					prev->rptr=tmp->rptr;
			}
			free(tmp);
		}
		else
		{
			prev=tmp->rptr;
		
			do{
				prev=prev->lptr;
			}while(prev->lptr!=NULL);

			x=tmp->ro;
			y=prev->ro;
			prev->ro=x;
			tmp->ro=y;
			prev->ro=f;
			delet(root,n);
		}
	}
}
void main()
{
	int ch,n;

	while(ch!=0)
	{
		printf("\n0.Exit \n1.Insert \n2.Display \n3.Delete \n");
		printf("Enter User Choice To Perform BST:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 0:
				exit(0);
			case 1:
				printf("Enter a value in Tree : ");
				scanf("%d",&n);
				insert(n);
				break;
			case 2:
				display(root);
				break;
			case 3:
				printf("Enter a value Delete in Tree : ");
				scanf("%d",&n);
				delet(root,n);
				break;

		}
	}
}