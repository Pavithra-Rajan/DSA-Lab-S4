#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct node
{
	int key;
	struct node* left ;
	struct node* right ;
	
}node;
struct stack
{
	long int A[10000];
	int top;
	int size;
}stack;

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
int ret_POP(struct stack *S)
{
 	int ret;
 	ret=S->A[S->top];
 	S->top=S->top-1;
 	return ret;
 		
 		//printf("%d\n",S->top);
 		//printf("%ld\n",S->A[S->top]);
 		
 		//printf("%d\n",S->top);	
}

node* create_tree(int val)
{
	node* root=(node*)malloc(sizeof(node));
	root->left=NULL;
	root->right=NULL;
	root->key=val;
	return root;
	
}
void Preorder(node *root) 
{
 	printf("( ");
	if (root != NULL) {
		
		printf("%d ", root->key);
		Preorder(root->left);
		Preorder(root->right);
		
	}
	printf(") ");
}
void extract_str(char str[], char str2[])
{
	int i;
	int j=0;
	for(i=1;i<strlen(str)-1;i++)
	{
		if(str[i]!=' ')
		{
			if(str[i]=='(' && str[i+2]==')')
				{
					i+=2;
					continue;
				}
			str2[j]=str[i];
			j++;
		}
	}
	//printf("%s ",str2);
	
		

}
int index_t(char str[],int start,int end)
{
	struct stack *S;
	int i;
	S=(struct stack*)malloc(sizeof(struct stack));
	S->size=100;
	S->top=-1;
	if(start>end)
		return -1;
	for(i=start;i<=end;i++)
	{
		if(str[i]=='(')
			PUSH(S,str[i]);
		else if(str[i]==')')
			if(S->A[S->top]='(')
				{
				POP(S);
				if(STACK_EMPTY(S)==-1)
					return i;
				}
	}
	return -1;
}
		
node* tree_insert(char str2[], int start, int end)
{
	
	
	if(start>end)
		return NULL;
	
	int num=0;
	
	
	int k;
	while(str2[start]>='0' && str2[start]<='9' && num<200)
		{
		num*=10;
		num=num+(str2[start]-'0');
		start++;

		}
	start--;
	//printf("%d ",num);
	
	node *root=create_tree(num);
	int i=-1;
	if(start+1<=end && str2[start+1]=='(')
		i=index_t(str2,start+1,end);
	if(i!=-1)
		{
		root->left=tree_insert(str2,start+2,i-1);
		root->right=tree_insert(str2,i+2,end-1);
		}
	return root;
		
		
}
int tree_height(node* root)
{
 	if(root==NULL)
 		return 0;
 	else 
 		{
 		 	int lh=tree_height(root->left);
 		 	int rh=tree_height(root->right);
 		 	if(lh>rh)
 		 		return lh+1;
 		 	else
 		 		return rh+1;
 		 }
}
void level(node *root, int lev,struct stack *S1)
{
	if(root==NULL)
		return;
	if(lev==0)
		{
		PUSH(S1,root->key);
		//POP(S1);
		}
	else
	{
		level(root->left,lev-1,S1);
		level(root->right,lev-1,S1);
	}
}
void cousins(int arr[],int i)
{
	//printf("in cousin func\n");
	int cous;
	scanf("%d",&cous);
	int j;
	int found=0;
	int elem_exist=0;
	for(j=0;j<i;j++)
	{
		//printf("loop\n");
		if(arr[j]==cous)
		
		{
			int lev=j+1;
			lev=(log10(lev)/log10(2));
			//printf("level->%d\n",lev);
			int up=pow(2,lev+1);
			up=up-2;
			int down=up-pow(2,lev)+1;
			elem_exist=1;
			//printf("%d %d %d\n",down,up,j);
			if(up>=i)
				up=i-1;
			if(up<i && down<i)
			   while(down<=up)
				{
					
					//printf("inside while\n");
					if((j%2==0 && down==j-1) || (j%2==1 && down==j+1) || down==j)
					down++;
					else
						{
						found=1;
						printf("%d ",arr[down]);
						down++;
						}
				}
				
		}
		//break;
	}
	if(found==0 && elem_exist==0)
		printf("-1\n");
			
				
					
}
void add_array(struct stack *S1)
{
	int arr[100];
	int i=0,j;
	struct stack *S2;
   	S2=(struct stack*)malloc(sizeof(struct stack));
    	S2->size=100;
  	S2->top=-1;
	while(STACK_EMPTY(S1)!=-1)
	{
		PUSH(S2,ret_POP(S1));
		//printf("%d ",arr[i]);
		//i++;
	}
	
	while(STACK_EMPTY(S2)!=-1)
	{
		arr[i]=ret_POP(S2);
		//printf("%d ",arr[i]);
		i++;
	}

	//printf("%d",i);
	//for(j=0;j<i;j++)
	//	printf("%d->",arr[j]);
	cousins(arr,i);
	
		
    	
}
void lev_elem(node* root) 
{
    if (root==NULL)
        return;
    struct stack *S1;
    S1=(struct stack*)malloc(sizeof(struct stack));
    S1->size=100;
    S1->top=-1;
    int height = tree_height(root);
    for (int i=0; i<height; i++) {
        //printf("Level %d: ", i);
        level(root, i,S1);
        //printf("\n");
    }
    add_array(S1);
    
}
node *BST_create(int arr[],int beg,int end)
{
	if(beg>end)
		return NULL;
	int mid=ceil((beg+end)/2);
	node *root=create_tree(arr[mid]);
	if(mid+1<=end)
	{
	root->left=BST_create(arr,beg,mid-1);
	root->right=BST_create(arr,mid+1,end);
	}
	return root;
}
void sum_lev_calc(node *root,int h, int arr[])
{
	if(root==NULL)
		return;
	arr[h]+=root->key;
	sum_lev_calc(root->left,h+1,arr);
	sum_lev_calc(root->right,h+1,arr);

}
int main()
{
	node *root=NULL;
	int size,i;
	scanf("%d",&size);
	int BST[size];
	for(i=0;i<size;i++)
		scanf("%d",&BST[i]);
	root=BST_create(BST,0,size-1);
	Preorder(root);
	int h=tree_height(root);
	int sum_lev[h];
	for(i=0;i<h;i++)
		sum_lev[i]=0;
	
	sum_lev_calc(root,0,sum_lev);
	printf("\n");
	for(i=0;i<h;i++)
		printf("%d ",sum_lev[i]);
	printf("\n");
	//int find;
	//scanf("%d",&find);
	//lev_elem(root);
	return 0;
	
}
