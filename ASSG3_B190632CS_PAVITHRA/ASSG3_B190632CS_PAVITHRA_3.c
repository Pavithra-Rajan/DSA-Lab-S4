#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	int data;
	struct node* left;
	struct node* right;
	struct node* p;
	int colour; // red 0, black 1
};

struct queue
{
	struct node* data;
	struct queue* next;
};
struct queue *front=NULL;
struct queue* rear=NULL;

struct node* front_inital()
{
	struct node *node;
	node=front->data;
	return node;
}
int queue_empty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}
void dequeue()
{
	if(queue_empty()!=0)
		return;
	struct queue* temp=front;
	front=front->next;
	free(temp);
}
void enqueue(struct node* data)
{
    struct queue* temp  =(struct queue*)malloc(sizeof(struct queue));
    temp->data = data;
    temp->next = NULL;

    if(front==NULL && rear == NULL)
    {
        front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
}
void LR(struct node **T,struct node** x)
{
	struct node* y=(*x)->right;
	(*x)->right=y->left;
	if(y->left!=NULL)
		y->left->p = *x;

        y->p = (*x)->p;

        if((*x)->p == NULL)
        	*T = y;

    	else if(*x == (*x)->p->left)
        	(*x)->p->left = y;

    	else
        	(*x)->p->right = y;

    	y->left = *x;

    	(*x)->p = y;
}
void RR(struct node **T,struct node** x)
{
	struct node* y=(*x)->left;
	(*x)->left=y->right;
	if(y->right!=NULL)
		y->right->p = *x;

        y->p = (*x)->p;

        if((*x)->p == NULL)
        	*T = y;

    	else if(*x == (*x)->p->left)
        	(*x)->p->left = y;

    	else
        	(*x)->p->right = y;

    	y->right = *x;

    	(*x)->p = y;
}
void RB_insert_aux(struct node** T, struct node** z)
{
    struct node* G = NULL;
    struct node* p_node = NULL;

    while(((*z)!=*T)&& ((*z)->colour!= 1) && ((*z)->p->colour == 0))
    {
        p_node = (*z)->p;
        G = (*z)->p->p;

        if(p_node == G->left)
        {
            struct node* uncle = G->right;

            if(uncle!=NULL && uncle->colour == 0)
            {
                G->colour = 0;
                p_node->colour = 1;
                uncle->colour = 1;
                *z = G;
            }

            else
            {
                if((*z) == p_node->right)
                {
                    LR(T,&p_node);
                    (*z) = p_node;
                    p_node = (*z)->p;
                }

                RR(T,&G);
                p_node->colour = 1;
                G->colour = 0;
                (*z) = p_node;
            }
        }

        else
        {
            struct node* uncle = G->left;

            if(uncle!=NULL && uncle->colour == 0)
            {
                G->colour = 0;
                p_node->colour = 1;
                uncle->colour = 1;
                (*z) = G;
            }

            else
            {
                if((*z) == p_node->left)
                {
                    RR(T,&p_node);
                    (*z) = p_node;
                    p_node = (*z)->p;
                }

                LR(T,&G);
                p_node->colour = 1;
                G->colour = 0;
                (*z) = p_node;
            }
        }
    }
    (*T)->colour = 1;

}

struct node* RB_insert(struct node* T,int data)
{
    struct node* z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->p = NULL;
    z->colour = 0;

    struct node* y = NULL;
    struct node* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(z->data < x->data)
            x = x->left;

        else
            x = x->right;
    }
    z->p = y;

    if(y==NULL)
        T = z;

    else if(z->data < y->data)
        y->left = z;

    else
        y->right = z;

    RB_insert_aux(&T,&z);

    return T;
}
void preorder(struct node* root)
{
  
    printf("( ");
    if(root != NULL)
    {
        if(root->colour==1)
        	printf("%d B ", root->data);
        else
        	printf("%d R ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
    printf(") ");

   
}
int main()
{
	struct node* root=NULL;
	int key;
	char elem[10];
	scanf("%s",elem);
	while(strcmp(elem,"t")!=0)
	{
		key=atoi(elem);
		root=RB_insert(root,key);
		preorder(root);
		printf("\n");
		scanf("%s",elem);
		if(strcmp(elem,"t")==0)
			break;
	}
	return 0;
}
