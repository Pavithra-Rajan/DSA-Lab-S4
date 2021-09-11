#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct node
{
	char *string;
	struct node* next;
};

int main()
{
	int size,i,hash,j,k;
	
	//str=malloc(sizeof(char)*500);
	scanf("%d",&size);
	
	//scanf("%s",str);
	//printf("%s\n",str);
	struct node* table[255];
	for(i=0;i<255;i++)
		table[i]=NULL;
	char str[size][500];
	for(i=0;i<size;i++)
	{
		hash=0;
		char checker[]={'a','b','c','d','e','f','g','h'};
		scanf("%s",str[i]);
		for(j=0;j<strlen(str[i]);j++)
			if(checker[str[i][j]-97]!='z')
				{
				hash+=pow(2,str[i][j]-97);
				checker[str[i][j]-97]='z';
				//printf("%s\n",checker);
				}
				
			
	
		struct node* new=malloc(sizeof(struct node));
		new->string=str[i];
		new->next=NULL;
		if(hash>=255)
			hash=hash%255;
		if(table[hash]==NULL)
			table[hash]=new;
		else
		{
			struct node *temp=table[hash];
			while(temp->next)
				temp=temp->next;
				
				
			temp->next=new;
			
			//else temp->next=NULL;
		}
		//printf("%s at %d\n",table[hash]->string,hash);
	
	}
	//printf("%s \n",table[35]->string);
	for(i=0;i<255;i++)
		{
		//printf("%d:",i);
		if(table[i]!=NULL)		
			{
			struct node*temp=table[i];
			//temp=temp->next;
			int count=0;
			while(temp)
			{
				//printf("-%s",temp->word);
				//printf("in while 1");
				temp=temp->next;
				count++;
				
			}
			//printf("%d ",count);
			temp=table[i];
			char comp[count][50],extra[50];
			int index=0;
			while(temp)
			{
				//printf("-%s",comp[index]);
				strcpy(comp[index],temp->string);
				
				temp=temp->next;
				index++;
			}
			for(j=0;j<count-1;j++)
				for(k=j+1;k<count;k++)
				{	//printf("%s-%s\n",comp[j],comp[k]);
					if(strcmp(comp[j],comp[k])>0)
					{
						//printf("comparing\n");
						strcpy(extra,comp[j]);
						strcpy(comp[j],comp[k]);
						strcpy(comp[k],extra);
					}
				}
			for(j=0;j<=count-1;j++)
				printf("%s ",comp[j]);
			
			printf("\n");
			}
		
		}
	
	return 0;

}
