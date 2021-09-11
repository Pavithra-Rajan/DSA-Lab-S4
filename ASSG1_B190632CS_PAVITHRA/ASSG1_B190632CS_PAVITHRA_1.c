#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int key;
	struct node* left ;
	struct node* right ;
	
}node;
typedef struct q_node
{
	node* k;
	struct q_node* link ;
	
	
}q_node;
typedef struct queue
{
	q_node* front;
	q_node* rear;
	int count;
}queue;
queue* create()
{
	queue* q=(queue*)malloc(sizeof(queue));
	
	q->front=NULL;
	q->rear=NULL;
	q->count=0;
	
	return q;
}
void enqueue(queue* q,node* x)
{
	q_node* new=(q_node*)malloc(sizeof(q_node));
	new->k=x;
	new->link=NULL;
	if(q->count==0)
		q->front=new;
	else
		q->rear->link=new;
	q->count++;
	q->rear=new;
}

node* dequeue(queue* q)
{
	if(q->count==0)
		return NULL;
	node *x=q->front->k;
	if(q->front->link)
	{
		q->front=q->front->link;
		q->count--;
	}
	else
	{
		q->front=NULL;
		q->rear=NULL;
		q->count--;
	}
	return x;
}

node* create_tree(int val)
{
	node* root=(node*)malloc(sizeof(node));
	root->left=NULL;
	root->right=NULL;
	root->key=val;
	return root;
	
}
void insert(node* root, node* n)
{
	queue* q=create();
	enqueue(q,root);
	while(q->count>0)
	{
		node *del=dequeue(q);
		if(del->left==NULL && del->right==NULL)
			{
			del->left=n;
			return;
			}
		else if(del->left==NULL)
			{
			del->left=n;
			return;
			}
		else if(del->right==NULL)
			{
			del->right=n;
			return;
			}
		else
		{
			enqueue(q,del->left);
			enqueue(q,del->right);
		}
	}
		
}

void Preorder(node *root) {
 	printf("( ");
	if (root != NULL) {
		
		printf("%d ", root->key);
		Preorder(root->left);
		Preorder(root->right);
		
	}
	printf(") ");
}
int main()
{
	node *root=NULL;
	char op;
	long int k;
	scanf("%c",&op);
	while(op!='e')
	{ 	switch(op)
		{
		 case 'i': scanf("%ld",&k);
		 	   if(root==NULL)
		 	   	root = create_tree(k);
		 	   else
			   	insert(root,create_tree(k));
		 	   break;
		 
		 case 'p': Preorder(root);
		 	   printf("\n");
		 	   
		 	   break;
		}
		scanf("%c",&op);
	}
	return 0;
}
