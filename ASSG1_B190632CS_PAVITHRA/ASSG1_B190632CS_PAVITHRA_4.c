#include<stdio.h>
#include<stdlib.h>
struct node
{
	long int key;
	struct node *left;
	struct node *right;
	struct node *p;
};
struct tree
{
	struct node *root;
};
struct stack
{
	long int A[10000];
	int top;
	int size;
};
int STACK_EMPTY(struct stack *S)
{
	if(S->top==-1)
		return -1;
	else
		return 1;
}
int STACK_FULL(struct stack *S)
{
	if(S->top==S->size-1)
		return 1;
	else
		return 0;
}
void PUSH(struct stack *S,long int k)
{
 	if(STACK_FULL(S)==1)
 		;
 	else
 	{	
 		//printf("%d\n",S->top);
 		
 		S->top=S->top+1;
 		//printf("%d\n",S->top);
 		S->A[S->top]=k;
 	}
}
void POP(struct stack *S)
{
 	if(STACK_EMPTY(S)==-1)
 		printf("-1\n");
 	else
 	{	
 		//printf("%d\n",S->top);
 		//printf("%ld\n",S->A[S->top]);
 		S->top=S->top-1;
 		//printf("%d\n",S->top);
 		
 	}
}
long int ret_POP(struct stack *S)
{
 	long int ret;
 	ret=S->A[S->top];
 	S->top=S->top-1;
 	return ret;
 		
 		//printf("%d\n",S->top);
 		//printf("%ld\n",S->A[S->top]);
 		
 		//printf("%d\n",S->top);	
}
struct node *search(struct node *x,long int k);
void INSERT(struct tree *T,struct node *z);
void TRANSPLANT(struct tree *T, struct node* x, struct node* y);
struct node* TREE_MIN(struct node *x);
long int DELETE(struct tree* T, struct node* x);
void INORDER(struct node *T);
void PREORDER(struct node *T);
void POSTORDER(struct node *T);
struct node *create_node(long int k)
{	
	struct node *x;
	x=(struct node*)malloc(sizeof(struct node));
	x->left=NULL;
	x->right=NULL;
	x->p=NULL;
	x->key=k;
	return x;
}

struct node *search(struct node *x,long int k)
{	
	
	if(x==NULL || x->key==k)
		return x;
	if(x->key<k)
		return search(x->right,k);
	return search(x->left,k);
				
}
void INSERT(struct tree *T,struct node *z)
{	
	
	long int k;
	scanf("%ld",&k);
	z=create_node(k);
	struct node* y=NULL;
	struct node* x=T->root;
	while(x!=NULL)
		{
			y=x;
			if(z->key<=x->key)
				x=x->left;
			else
				x=x->right;
		}
	z->p=y;
	if(y==NULL)
		T->root=z;
	else if(z->key<y->key)
		y->left=z;
	else
		y->right=z;
		
		
}
void TRANSPLANT(struct tree *T, struct node* x, struct node* y)
{
	if(x->p==NULL)
		T->root=y;
	else if(x==x->p->left)
		x->p->left=y;
	else 
		x->p->right=y;
	if(y!=NULL)
		y->p=x->p;
}
struct node* TREE_MIN(struct node *x)
{
	while(x->left!=NULL)
		x=x->left;
	return x;
}
struct node* TREE_MAX(struct node *x)
{
	while(x->right!=NULL)
		x=x->right;
	return x;
}
long int DELETE(struct tree* T, struct node* x)
{
	x=T->root;
	long int k;
	scanf("%ld",&k);
	x=search(x,k);
	if(x==NULL)
		return -1;
	else{
	if(x->left==NULL)
		TRANSPLANT(T,x,x->right);
	else if(x->right==NULL)
		TRANSPLANT(T,x,x->left);
	else 
		{
		struct node* y=TREE_MIN(x->right);
		if(y->p!=x)
			{
			TRANSPLANT(T,y,y->right);
			y->right=x->right;
			y->right->p=y;
			}
		TRANSPLANT(T,x,y);
		y->left=x->left;
		y->left->p=y;
		}
	return k;
	}
		
}
void INORDER(struct node *T)
{
	if(T!=NULL)
	{
		INORDER(T->left);
		printf("%ld ",T->key);
		INORDER(T->right);
	}

}
void INORDER_P(struct node *T,struct stack *S)
{
	
	if(T!=NULL)
	{
		INORDER_P(T->left,S);
		PUSH(S,T->key);
		//printf("%ld ",T->key);
		INORDER_P(T->right,S);
	}

}
void PREORDER(struct node *T)
{
	if(T!=NULL)
	{
		printf("%ld ",T->key);
		PREORDER(T->left);
		PREORDER(T->right);
	}
}
void POSTORDER(struct node *T)
{
	if(T!=NULL)
	{
		POSTORDER(T->left);
		POSTORDER(T->right);
		printf("%ld ",T->key);
	}

}
int get_elem(struct node *T,long int find,int l)
{
	if(T==NULL)
		return 0;
	if(T->key==find)
		return l;
	int downwards=get_elem(T->left,find,l+1);
	if(downwards!=0)
		return downwards;
	downwards=get_elem(T->right,find,l+1);
	return downwards;
}
int LEVEL(struct node* T, long int find)
{
	return get_elem(T,find,1);
}
struct node* SUCCESSOR(struct node* x)
{
	if(x->right!=NULL)
		return TREE_MIN(x->right);
	struct node* y= x->p;
	while(y!=NULL && x==y->right)
		{
		x=y;
		y=y->p;
		}
	return y;
		
}
void PREDECESSOR(struct node* T, long int key)
{
	struct stack* S;
	S=(struct stack*)malloc(sizeof(struct stack));
	S->size=500;
	S->top=-1;
	long int popped;
	INORDER_P(T,S);
	while(STACK_EMPTY(S)!=-1)
	{
		popped=ret_POP(S);
		if(popped==key)
		{
			printf("%ld\n",ret_POP(S));
			break;
		}
	}
	
	 
	
    
} 
  


int main()
{	
	struct tree *T;
	struct node *x;
	struct node *y;
	T=(struct tree*)malloc(sizeof(struct tree));
	T->root=NULL;
	char op;
	long int k;
	long int find;
	scanf("%c",&op);
	while(op!='e')
	{ 	switch(op)
		{
		 case 'a': INSERT(T,x);
		 	   break;
		 case 'd': printf("%ld\n",DELETE(T,x));
		 	   break;
		 case 's': scanf("%ld",&k);
		 	   if(search(T->root,k)!=NULL)
		 	   	printf("1\n");
		 	   else
		 	   	printf("-1\n");
		 	   break;
		 case 'l': 
		 	   scanf("%ld",&find);
		 	   if(LEVEL(T->root,find)==0)
		 	   	printf("-1\n");
		 	   else
		 	   	printf("%d\n",LEVEL(T->root,find));
		 	   break;
		 case 'm': y=TREE_MIN(T->root);
		 	   printf("%ld\n",y->key);
		 	   break;
		 case 'u': scanf("%ld",&k);
		 	   if(search(T->root,k)!=NULL && k!=TREE_MAX(T->root)->key)
		 	   	{
		 	   	y=SUCCESSOR(search(T->root,k));
		 	   	printf("%ld\n",y->key);
		 	   	}
		 	   else
		 	   	printf("-1\n");
		 	   break;
		 case 'r': scanf("%ld",&k);
		 	   if(search(T->root,k)!=NULL && k!=TREE_MIN(T->root)->key)
		 	   	{
		 	   	PREDECESSOR(T->root,k);
		 	   	
		 	   	}
		 	   else
		 	   	printf("-1\n");
		           
		 	   break;
		 case 'x': y=TREE_MAX(T->root);
		 	   printf("%ld\n",y->key);
		 	   break;
		 case 'i': INORDER(T->root);
		 	   printf("\n");
		 	   break;
		 case 'p': PREORDER(T->root);
		 	   printf("\n");
		 	   break;
		 case 't': POSTORDER(T->root);
		 	   printf("\n");
		 	   break;
		 		  		 	   
		}
		scanf("%c",&op);
	}
 	return 0;	 	  		 
}
