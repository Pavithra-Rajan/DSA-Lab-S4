#include<stdio.h>
#include<stdlib.h>

int count_a=0,count_b=0,count_c=0,count_d=0;
int error=0;
int flag=0;
struct set1
{
	int key;
	struct set1* rep;
};
struct set1 *find_a,*find_c,*found_a,*set1_node;

struct set2
{
	int key;
	struct set2* rep;
	int rank;
};
struct set2 *find_b,*find_d,*set2_node,*set2_node_d,*set2_node_b;

struct l1
{
	struct set1* node;
}*a1,*a2;

struct l2
{
	struct set2* node;
}*a3,*a4;

int i=0,j=0,k=0,l=0;


void MAKESET(int val)
{
	if(a1[val].node!=NULL)
		{
		printf("-1");
		return;
		}
	printf("%d ",val);
	
	set1_node=(struct set1*)malloc(sizeof(struct set1));
	struct set1 *node_a;
	
	node_a=(struct set1*)malloc(sizeof(struct set1));
	struct set2* node_b=(struct set2*)malloc(sizeof(struct set2));
	
	set1_node->key=val;
	node_a->key=val;
	
	set1_node->rep=set1_node;
	node_a->rep=node_a;
	
	a1[val].node=set1_node;
	a2[val].node=node_a;
	i++;
	j++;
	
	set2_node_b=(struct set2*)malloc(sizeof(struct set2));
	set2_node_b->key=val;
	set2_node_b->rep=set2_node_b;
	set2_node_b->rank=0;
	
	node_b->key=val;
	node_b->rep=node_b;
	node_b->rank=0;
	
	a3[val].node=set2_node_b;
	a4[val].node=node_b;
	k++;
	l++;
}

struct set1* FIND_A(int val)
{
	flag=0;
	found_a=a1[val].node;
	
	if(a1[val].node!=NULL)
	{
		count_a++;
		found_a=a1[val].node;
		flag=1;
		while(found_a)
		{
			if(found_a->rep==found_a)
				break;
			else
				found_a=found_a->rep;
			count_a++;
		}
	}
	return found_a;
}
void UNION_A(int v,int w)
{
	error=0;
	set1_node=(struct set1*)malloc(sizeof(struct set1));
	struct set1*new3=(struct set1*)malloc(sizeof(struct set1));
	
	set1_node=FIND_A(v);
		if(flag==0)
			{
				printf("-1 ");
				error=1;			
				return;
			}
	new3=FIND_A(w);
		if(flag==0)
			{
				printf("-1 ");
				error=1;
				return;
			}
	if(set1_node->key==new3->key)
	{
		printf("%d ",set1_node->key);
	}
	else
	{
		new3->rep=set1_node;
		printf("%d ",set1_node->key);
	}
}

int exist_B=0;
struct set2* FIND_B(int val)
{
	exist_B=0;
	if(a1[val].node==NULL)
	{
		set2_node=NULL;
		return set2_node;
	}
	exist_B=1;
	set2_node=a3[val].node;
	count_b++;
	while(set2_node)
	{
		if(set2_node->rep==set2_node)
			break;
		else
			set2_node=set2_node->rep;
		count_b++;
	}
	return set2_node;
}

void UNION_B(int v,int w)
{
	set2_node_b=(struct set2*)malloc(sizeof(struct set2));
	struct set2*new4=(struct set2*)malloc(sizeof(struct set2));
	set2_node_b->rank=new4->rank=0;
	
	set2_node_b=FIND_B(v);
	if(exist_B==0)
		{
			printf("-1 ");
			return;
		}
	new4=FIND_B(w);
	if(exist_B==0)
		{
			printf("-1 ");
			return;
		}

	if(set2_node_b->rank>new4->rank)
		{
			new4->rep=set2_node_b;
			printf("%d ",set2_node_b->key);
		}
	else if(set2_node_b->rank<new4->rank)
		{
			set2_node_b->rep=new4;
			printf("%d ",new4->key);
		}
	else
		{
			new4->rep=set2_node_b;
			printf("%d ",set2_node_b->key);
			
			(set2_node_b->rank)++;
		}
		//printf("rank union");

}

struct set1* path_conv(struct set1 * b)
{
	if(b!=b->rep)
		b->rep=path_conv(b->rep);
	count_c++;
	return b->rep;

}


int exist_C=0;

struct set1* FIND_C(int val)
{

	exist_C=0;
	if(a1[val].node==NULL)
	{
		find_a=NULL;
		return find_a;
	}
	
	exist_C=1;
	find_a=path_conv(a2[val].node);
	return find_a;
}

void UNION_C(int v,int w)
{
	set1_node=(struct set1*)malloc(sizeof(struct set1));
	struct set1*new3=(struct set1*)malloc(sizeof(struct set1));
	
	set1_node=FIND_C(v);
		if(exist_C==0)
		{
			printf("-1 ");
			return;
		}
	new3=FIND_C(w);
		if(exist_C==0)
		{
			printf("-1 ");
			return;
		}
	if(set1_node->key==new3->key)
		printf("%d ",set1_node->key);
		
	else
	{
		new3->rep=set1_node;
		printf("%d ",set1_node->key);
	}
}	

struct set2* path_conv_d(struct set2 * h)
{
	count_d++;
	if(h!=h->rep)
		h->rep=path_conv_d(h->rep);
	return h->rep;
}


int exist_D=0;

struct set2* f4(int val)
{
	exist_D=0;
	if(a1[val].node==NULL)
	{
		set2_node_d=NULL;
		return set2_node_d;
	}
	exist_D=1;
	
	set2_node_d=path_conv_d(a4[val].node);
	return set2_node_d;
}

void UNION_D(int v,int w)
{
	struct set2*temp=(struct set2*)malloc(sizeof(struct set2));
	struct set2*temp2=(struct set2*)malloc(sizeof(struct set2));
	
	temp->rank=temp2->rank=0;
	temp=f4(v);
		if(exist_D==0)
			{
				printf("-1 ");
				return;
			}
	temp2=f4(w);
		if(exist_D==0)
			{
				printf("-1 ");
				return;
			}

	if(temp->rank>temp2->rank)
		{
			temp2->rep=temp;
			printf("%d ",temp->key);
		}
	else if(temp->rank<temp2->rank)
		{
			temp->rep=temp2;
			printf("%d ",temp2->key);
		}
	else
		{
			temp2->rep=temp;
			printf("%d ",temp->key);
			//printf("Rank applied");
			(temp->rank)++;
		}
}

void data_accesses()
{
	printf("%d %d %d %d",count_a,count_b,count_c,count_d);
	printf("\n");
}


int main()
{
	a1=(struct l1*)malloc(10000*sizeof(struct l1));
	
	int i;
	for(i=0;i<10000;i++)
		a1[i].node=NULL;
	a2=(struct l1*)malloc(10000*sizeof(struct l1));
	a3=(struct l2*)malloc(10000*sizeof(struct l2));
	a4=(struct l2*)malloc(10000*sizeof(struct l2));

	char op;
	int elem,elem2;

	do
	{
		scanf(" %c",&op);
		switch(op)
		{
			case 'm': 
					scanf("%d",&elem);
					
					MAKESET(elem);
					printf("\n");
					break;

			case 'f':
					scanf("%d",&elem);
					

					find_a=FIND_A(elem);
					if(flag==0)
						{
						 	printf("-1 -1 -1 -1\n");
						 	break;
						}
					else
					{
						 
						printf("%d ",find_a->key);
						
						find_b=FIND_B(elem);
						printf("%d ",find_b->key);
						
						find_c=FIND_C(elem);
						printf("%d ",find_c->key);
						
						find_d=f4(elem);
						printf("%d ",find_d->key);
						
						printf("\n");
					}
					break;

			case 'u':
					scanf("%d%d",&elem,&elem2);
					

					UNION_A(elem,elem2);
					if(error==1)
					{
						printf("-1 -1 -1\n");
						break;
					}
					UNION_B(elem,elem2);
					UNION_C(elem,elem2);
					UNION_D(elem,elem2);
					printf("\n");
					break;

			case 's':
					data_accesses();
					break;

			
		}
	}while(op!='s');

	return 0;
}
