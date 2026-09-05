#include <stdio.h>

int main()
{
    int a[100], n, i,j, key, choice;
    int found, low, high, mid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("\n******** SEARCH MENU *********\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter element to search: ");
    scanf("%d", &key);

    switch(choice)
    {
        case 1:
            /* Linear Search */
            found = 0;

            for(i=0; i<n; i++)
            {
                if(a[i] == key)
                {
                    printf("Element found \n");
                    found = 1;
                    break;
                }
            }

            if(found == 0)
            {
                printf("Element not found\n");
            }
            break;

		case 2:
			/* Binary Search */

			for(i=0; i<n-1; i++)
			{
				for(j=0; j<n-i-1; j++)
				{
					if(a[j] > a[j+1])
					{
						int temp = a[j];
						a[j] = a[j+1];
						a[j+1] = temp;
					}
				}
			}
			
			low = 0;
			high = n-1;
			found = 0;

			while(low <= high)
			{
				mid = (low+high)/2;

				if(a[mid]==key)
				{
					printf("Element found \n");
					found = 1;
					break;
				}
				else if(key<a[mid])
				{
					high=mid-1;
				}
				else
				{
					low=mid+1;
				}
			}

			if(found == 0)
			{
				printf("Element not found\n");
			}
			break;
		}
	

	return 0;
		
}



