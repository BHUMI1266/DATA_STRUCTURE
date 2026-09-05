#include<stdio.h>

void radix(int a[],int value)
{
	int i,j,k;
	int max=a[0];
	int place=1;
	int b[100];
	
	for(int i=0;i<=value;i++)
	{
		if(a[i]>max)
		{
			max=a[i];
		}
	}
	
	while(max/place>0)
	{
		for(i=0;i<10;i++)
		{
			count[i]=0;
		}
	}
	for(int i=0;i<=value;i++)
	{
		count[(a[i]/place)%10]++;
	
	}
	for(i=1;i<10;i++)
	{
		count[i]=count[i]+count[i-1];
	}
	for(i=n-1;i>=0;i--)
	{
		k=(a[i]/place)%10;
		b[count[k]-1]=a[i];
		count[k]--;
	}
	for(i=0;i<value;i++)
	{
		a[i]=b[i];
		place=place*10;
	}
}

int main()
{
	int a[100];
	int n,i;
	
	printf("\n enter nmber of element :");
	scanf("%d",&n);
	
	printf("\n enter element:");
	
	
	for(i=0;i<value;i++)
	{
		scanf("%d",&a[i]);
	}
	
	radix(a,value);
	
	printf("\n Sorted elements:");
	for(i=0;i<value;i++)
	{
		scanf("%d",a[i]);
	}
	return 0;
}
	