#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
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
void INORDER(struct node *T)
{
	if(T!=NULL)
	{
		INORDER(T->left);
		printf("%ld ",T->key);
		INORDER(T->right);
	}

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
	
	char numbers[500];
	scanf("%[^\n]",numbers);
	char *token=strtok(numbers," ");
	while(token!=NULL)
	{
		int k=atoi(token);
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
		token=strtok(NULL," ");
	}
		
		
}
int maxim(int a,int b)
{
	return(a>b?a:b);
}
int max_paths(struct node* root, int k, int l)
{
    int min=INT_MIN;
    if((root->key==k || root->key==l) && root->left!=NULL)
    {
        min=root->left->key;
        if(root->left->key<l)
            root=root->left;
    }
    while(root!=NULL && (root->key!=k && root->key!=l))
    {
        if(root->key>min)
            min=root->key;
        if(k>root->key)
            root=root->right;
        else
            root=root->left;
    }
    return min;
}

int find_path(struct node *root, int a,int b)
{
    if(root==NULL)
        return 0;
    while((a<root->key && b<root->key) || (a>root->key && b>root->key))
        {
        if(a<root->key && b<root->key)
            root=root->left;
        if(a>root->key && b>root->key)
            root=root->right;
        }
    return maxim(max_paths(root,a,b),max_paths(root,b,a));
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
	INSERT(T,x);
	//INORDER(T->root);
	int a,b;
	scanf("%d %d",&a,&b);
	
	printf("%d\n",find_path(T->root,a,b));	 
 	return 0;	 	  		 
}
