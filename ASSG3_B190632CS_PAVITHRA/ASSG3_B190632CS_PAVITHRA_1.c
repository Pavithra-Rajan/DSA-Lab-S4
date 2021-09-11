#include<stdio.h>
#include<stdlib.h>
  
struct node
{
    int data;
    struct node *left;
    struct node *right;
    int height;
};
  
int height(struct node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int max_two_num(int a, int b)
{
    if(a<b)
    	return b;
    else
    	return a;
}
  

struct node* new_element(int data)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->data   = data;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

struct node *RR(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
  
    x->right = y;
    y->left = T2;
  
    
    y->height = max_two_num(height(y->left), height(y->right))+1;
    x->height = max_two_num(height(x->left), height(x->right))+1;
  
    return x;
}
  

struct node *LR(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
  
    
    y->left = x;
    x->right = T2;
 
    x->height = max_two_num(height(x->left), height(x->right))+1;
    y->height = max_two_num(height(y->left), height(y->right))+1;
  
    return y;
}
  

int balance_factor(struct node *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}
  
struct node* insert(struct node* node, int data)
{
   
    if (node == NULL)
        return(new_element(data));
  
    if (data < node->data)
        node->left  = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else 
        return node;
  
    
    node->height = 1 + max_two_num(height(node->left),
                           height(node->right));
  
   
    int balance = balance_factor(node);
  
    if (balance > 1 && data < node->left->data)
        return RR(node);
  
    
    if (balance < -1 && data > node->right->data)
        return LR(node);
  
    
    if (balance > 1 && data > node->left->data)
    {
        node->left =  LR(node->left);
        return RR(node);
    }
  
    if (balance < -1 && data < node->right->data)
    {
        node->right = RR(node->right);
        return LR(node);
    }
  
   
    return node;
}

struct node * minimum(struct node* node)
{
    struct node* min = node;
  
    
    while (min->left != NULL)
        min = min->left;
  
    return min;
}
  

struct node* DELETE(struct node* root, int data)
{
    if (root == NULL)
        return root;
  
  
    if ( data < root->data )
        root->left = DELETE(root->left, data);
  
    
    else if( data > root->data )
        root->right = DELETE(root->right, data);
  
   
    else
    {
        
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left :
                                             root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            free(temp);
        }
        else
        {
            struct node* temp = minimum(root->right);
  
            
            root->data = temp->data;
  
            
            root->right = DELETE(root->right, temp->data);
        }
    }
  
    
    if (root == NULL)
      return root;
  
    root->height = 1 + max_two_num(height(root->left),
                           height(root->right));
  
    
    int balance = balance_factor(root);
  
    
    if (balance > 1 && balance_factor(root->left) >= 0)
        return RR(root);
  
    if (balance > 1 && balance_factor(root->left) < 0)
    {
        root->left =  LR(root->left);
        return RR(root);
    }
  
    
    if (balance < -1 && balance_factor(root->right) <= 0)
        return LR(root);
  
    
    if (balance < -1 && balance_factor(root->right) > 0)
    {
        root->right = RR(root->right);
        return LR(root);
    }
  
    return root;
}

void preorder(struct node *root)
{
	printf("( ");
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
    printf(") ");
}
 int search(struct node *root,int element)
{
	while(root!=NULL)
	{
		if(element<root->data)
			return search(root->left,element);
		else if(element>root->data)
			return search(root->right,element);
		else
			return 1;
	}
	return 0;
}
struct node* search_elem(struct node *root,int element)
{
	while(root!=NULL)
	{
		if(element<root->data)
			return search_elem(root->left,element);
		else if(element>root->data)
			return search_elem(root->right,element);
		else
			return root;
	}
	return NULL;
} 

int main()
{
  struct node *root = NULL;
  struct node* temp=NULL;
	int k,del,ans,element;
	char op;
	int searched;
	scanf("%c",&op);
	while(op!='e')
	{
		switch(op)
		{
			case 'i':
				scanf("%d",&k);
				root=insert(root,k);
				break;
			case 'p':
				
				preorder(root);
				printf("\n");
				break;
			case 'd':
				scanf("%d",&del);
				
				ans=search(root,del);
				if(ans==0)
					printf("FALSE\n");
				else
					{
					root = DELETE(root,del);
					printf("%d\n",del);
					}
							
				break;
				
			case 's':
				scanf("%d",&element);
				ans=search(root,element);
				if(ans==1)
					printf("TRUE\n");
				else
					printf("FALSE\n");
				break;
			case 'b':
				scanf("%d",&element);
				temp=search_elem(root,element);
				if(temp!=NULL)
					printf("%d\n",balance_factor(temp));
				else
				  	printf("FALSE\n");
				break;
			
		}
		scanf("%c",&op);
		
	}
	return 0;
  
}
