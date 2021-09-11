#include<stdio.h>
int main()
{
	int size;
	scanf("%d",&size);
	int AdjMat[size][size];
	int i,j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			scanf("%d",&AdjMat[i][j]);
	for(i=0;i<size;i++)
	{
		printf("%d ",i);
		for(j=0;j<size;j++)
			if(AdjMat[i][j]==1)
				printf("%d ",j);
		printf("\n");
	}
	
	return 0;
		
}
