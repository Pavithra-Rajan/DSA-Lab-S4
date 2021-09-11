#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
	char *word;
	struct node* next;
};

int main()
{
	int size;
	char str[500];
	//str=malloc(sizeof(char)*500);
	scanf("%d %[^\n]s",&size,str);
	//scanf("%s",str);
	//printf("%s\n",str);
	int hash;
	
	struct node* table[size];
	for(int i=0;i<size;i++)
		table[i]=NULL;
		
	char *token=strtok(str," ");
	int mult_occur=0;
	while(token!=NULL)
	{
	//printf("%s\n",token);
	hash=(strlen(token)*strlen(token))%size;
		struct node* new=malloc(sizeof(struct node));
		new->word=token;
		new->next=NULL;
		if(table[hash]==NULL)
			table[hash]=new;
		else
		{
			struct node *temp=table[hash];
			while(temp->next)
				{
				if(strcmp(temp->word,token)!=0)
					temp=temp->next;
				else
					{
					mult_occur=1;
					break;
					}
				
				}
			if(strcmp(temp->word,token)==0)
				mult_occur=1;
			if(mult_occur!=1)
				temp->next=new;
			//else temp->next=NULL;
		}
	token=strtok(NULL," ");
	mult_occur=0;
	}
	for(int i=0;i<size;i++)
		{
		printf("%d:",i);
		if(table[i]==NULL)
			{
			printf("null\n");
			continue;
			}
		else
		{
			printf("%s",table[i]->word);
			struct node*temp=table[i];
			temp=temp->next;
			while(temp)
			{
				printf("-%s",temp->word);
				temp=temp->next;
			}
		}
		printf("\n");
		}
	
	return 0;

}
