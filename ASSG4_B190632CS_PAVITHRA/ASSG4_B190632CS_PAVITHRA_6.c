#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<math.h>

typedef struct node 
{
    int key;
    int degree;
    
    bool mark;
    bool reach_sear; //used while searching
    
    struct node *left_sibling;
    struct node *right_sibling;
    struct node *parent;
    struct node *child;
    
}node;

typedef struct fib_heap 
{
    int size;
    node *min;
    int degree;
}fib_heap;

void fib_heap_link(fib_heap *H, node *y, node *x); 


fib_heap *MAKE_HEAP() 
{
    fib_heap *H;
    H = (fib_heap*)malloc(sizeof(fib_heap));
    H->size = 0;
    H->min = NULL;
    H->degree = 0;
    return H;
}
void new_print_heap(node *n)
{
	node *x;
for (x= n; ; x = x->right_sibling) 
	{
           
            if( x->child == NULL)
             {
                printf("childless (%d) \n", x->key);
            } else {
            	
            		printf("(%d) has child (%d)\n", x->key, x->child->key);
                new_print_heap(x->child);
            }
            if(x->right_sibling == n) 
            {
                break;
            }
    }
}
typedef struct node_ll
{
	node *key;
   	struct node_ll *next;
}*node_ll;

typedef struct queue
{
	node_ll head;
 	node_ll tail;
}*queue;

int QUEUE_EMPTY(queue Q)
{
   if(Q->head==NULL)
     return 0;
   else
     return 1;
}
node_ll CREATENODE(node *k)
{
	 node_ll temp;
	 temp=(node_ll)malloc(sizeof(struct node_ll));
	 temp->key=k;
	 temp->next=NULL;
	 return temp;
}
void ENQUEUE(queue Q,node *y)
{
	node_ll x=CREATENODE(y);
	//printf("%d",y->key); 
 	if(QUEUE_EMPTY(Q)==0)
   		Q->head=x;
 	else
    		Q->tail->next=x;
  		Q->tail=x;
  	//printf("enqueued");
 
}

void DEQUEUE(queue Q)
{
   if(QUEUE_EMPTY(Q)!=0)
     {
        node_ll temp=Q->head;
        if(Q->head==Q->tail)
          Q->tail=NULL;
        Q->head=Q->head->next;
         
}
//return temp->data;
}
void QUEUE_DELETE(queue Q)
{
    
   while(QUEUE_EMPTY(Q)!=0)
    {
      DEQUEUE(Q);
    }
  
}
void level_order_aux(node *root_q)
{
  if(root_q==NULL)
    return;
  printf("%d ", root_q->key) ;
  if(root_q->child==NULL)
    return;

   queue Q;
   Q=(queue)malloc(sizeof(struct queue));
   Q->head=NULL;
   Q->tail=NULL;
   
   node *present=root_q->child;
   ENQUEUE(Q,present);
   node *loop_tree;
   
   while(QUEUE_EMPTY(Q)!=0)
     {
       node *temp;
       temp=Q->head->key;
       loop_tree=Q->head->key;
       
       DEQUEUE(Q);
        while(loop_tree!=NULL)
          {
              //printf("in while");
              printf("%d ",loop_tree->key);
              if(loop_tree->child!=NULL)
                   ENQUEUE(Q,loop_tree->child);
              loop_tree=loop_tree->right_sibling;
              if(loop_tree==temp)
              	/*{
              	if(loop_tree->child!=NULL)
              		{
              		loop_tree=loop_tree->child;
              		while(QUEUE_EMPTY(Q)!=0)
              		{
              			node* loop=Q->head->key;
       			printf("%d ",loop->key);
       			DEQUEUE(Q);
              		}
              		level_order_aux(loop_tree);
              		}
              	else*/
              	  break;
              	  
              		
           }
         
    }
}
void level_order_2(node* h)
{
    node* temp=h;
    while(h!=NULL)
    { 

        level_order_aux(h);

        h=h->right_sibling;
        if(h->key==temp->key)
        	break;
       
     }
 //printf("\n");
}
void print_final(node* h)
{
	node* temp=h;
	while(h!=NULL)
	{
		printf("%d ",h->key);
		h=h->right_sibling;
		if(h==temp)
			break;
	}
	
}
void INSERT(fib_heap *H,node *new, int val) 
{ 
    new = (node*)malloc(sizeof(node)); 
    new->key = val;
    new->degree = 0;
    new->mark = false; 
    new->parent = NULL; 
    new->child = NULL;
    new->reach_sear = false; 
    new->left_sibling = new; 
    new->right_sibling = new; 
    if (H->min == NULL)
    { 
        H->min = new; 
    } 
    else    
    { 
        H->min->left_sibling->right_sibling = new; 
        new->right_sibling = H->min; 
        new->left_sibling = H->min->left_sibling; 
        H->min->left_sibling = new; 
        if (new->key < H->min->key)
        {
            H->min = new;
        }          
    }
    (H->size)++; 
}

node *find_min_node(fib_heap *H)
{
    if(H==NULL)
    	return NULL;
    
    return H->min;
}


int deg_calc(int size)
{
    int c= 0;
    while (size>0)
    {
        size=size/2;
        c++;
    }
    return c;
}
void CONSOLIDATE(fib_heap *H)
{
    int degree,i,d;
    degree = deg_calc(H->size);
    node *A[degree], *x, *y, *z;
    for(i=0;i<=degree;i++)
    {
        A[i] = NULL;
    }
    x = H->min;
    do
    {
        d = x->degree;
        while (A[d]!=x && A[d]!=NULL)
        {
            
            y = A[d];
            if(x->key > y->key)
            {
                node *temp;
                temp = x;
                x = y;
                y = temp;
            }
            if(y == H->min)
                H->min = x;
                
            fib_heap_link(H,y,x);
            if(y->right_sibling == x)
                H->min = x;
            A[d] = NULL;
            d=d+1;
        }
        A[d] = x;
        x = x->right_sibling;
    } while(x!=H->min);

    H->min = NULL;
    for(i=0;i<degree;i++)
    {
        if(A[i]!= NULL)
        {
            A[i]->left_sibling = A[i];
            A[i]->right_sibling = A[i];
            if(H->min == NULL)
            {
                H->min = A[i];
            }
            else
            {
                H->min->left_sibling->right_sibling = A[i];
                A[i]->right_sibling = H->min;
                A[i]->left_sibling = H->min->left_sibling;
                H->min->left_sibling = A[i];
                if(A[i]->key < H->min->key)
                {
                    H->min = A[i];
                }
            } 
            if (H->min == NULL)
            {
                H->min = A[i];
            }
            else if(A[i]->key<H->min->key)
            {
                H->min = A[i];
            }            
              
        }
    }
} 

void fib_heap_link(fib_heap *H, node *y, node *x)
{
    //printf("(%d-%d)\n",y->key,x->key);
    y->right_sibling->left_sibling = y->left_sibling;
    y->left_sibling->right_sibling = y->right_sibling;

    if(x->right_sibling == x)
        H->min = x;

    y->left_sibling = y;
    y->right_sibling = y;
    y->parent = x;

    if(x->child == NULL)
    {
        x->child = y;
    }
    y->right_sibling = x->child; 
    y->left_sibling = x->child->left_sibling; 
    x->child->left_sibling->right_sibling = y; 
    x->child->left_sibling = y;
    if ((y->key) < (x->child->key)) 
        x->child = y; 
    
    (x->degree)++;  
}
node *extract_min(fib_heap * H) 
{ 
    
    if (H->min != NULL) 
     { 
        node* temp = H->min; 
        node* pntr; 
        pntr = temp; 
        node* x = NULL; 
        //printf("in extract");
        if (temp->child != NULL) 
        { 
  
            x = temp->child; 
            do { 
                pntr = x->right_sibling; 
                (H->min->left_sibling)->right_sibling = x; 
                x->right_sibling = H->min; 
                x->left_sibling = H->min->left_sibling; 
                H->min->left_sibling = x; 
                if (x->key < H->min->key) 
                    H->min = x; 
                x->parent = NULL; 
                x = pntr; 
            } while (pntr != temp->child); 
        }
        
        (temp->left_sibling)->right_sibling = temp->right_sibling; 
        (temp->right_sibling)->left_sibling = temp->left_sibling; 
        H->min = temp->right_sibling; 
       // printf("exchange done\n");
        if (temp == temp->right_sibling && temp->child == NULL) 
            H->min = NULL; 
        else { 
            H->min = temp->right_sibling; 
            CONSOLIDATE(H); 
             } 
        H->size = H->size-1; 
        return temp;
    } 
    return H->min;
} 

void CUT(fib_heap *H, node *dec_node, node * child_cut)
{
    node *temp_parent_check;

    if(dec_node == dec_node->right_sibling)
        child_cut->child = NULL;

    
    dec_node->left_sibling->right_sibling = dec_node->right_sibling;
    dec_node->right_sibling->left_sibling = dec_node->left_sibling;
    if(dec_node == child_cut->child)
        child_cut->child = dec_node->right_sibling;
    (child_cut->degree)--;

    //add to the root list
    dec_node->left_sibling = dec_node;
    dec_node->right_sibling = dec_node;
    H->min->left_sibling->right_sibling = dec_node; 
    dec_node->right_sibling = H->min; 
    dec_node->left_sibling = H->min->left_sibling; 
    H->min->left_sibling = dec_node;

    //mark false
    dec_node->parent = NULL;
    dec_node->mark = false;    
}

void CASCADING_CUT(fib_heap *H, node *child_cut)
{
    node *par_cut;
    par_cut= child_cut->parent;
    if(par_cut!=NULL)
    {
        if(child_cut->mark == false)
        	child_cut->mark= true;
        
        else
        {
            CUT(H,child_cut,par_cut);
            CASCADING_CUT(H,par_cut);
        }
    }
}

void DECREASE_KEY(fib_heap * H,node *dec_node, int new_key)
{
    node *par_dec;
    if(H == NULL)
        return;
    
    if(dec_node == NULL)
    	return;
    
    else
    {
        if(dec_node->key < new_key)
		return;
        else
        {
            dec_node->key = new_key;
            par_dec = dec_node->parent;
            if((par_dec!=NULL) && (dec_node->key < par_dec->key))
            {
                //printf("in else");
                CUT(H, dec_node, par_dec);
                CASCADING_CUT(H, par_dec);
            }
            if(dec_node->key < H->min->key)
            	H->min = dec_node;
            
        }
    }
   
}

void SEARCH_NODE(fib_heap *H,node *n, int key,int new_key)
{
    node *search_trav=n;
    node *temp=NULL;
    search_trav->reach_sear = true;
    
    if(search_trav->key == key)
    {
        search_trav->reach_sear = false;
        temp=search_trav;
        if(new_key==INT_MIN)
        	printf("%d\n",key);
        else 
        	printf("%d\n",new_key);
        DECREASE_KEY(H,temp,new_key);
        //return 1;
    }
     if(search_trav->child!=NULL)
	 SEARCH_NODE(H,search_trav->child, key,new_key);
	    
     if((search_trav->right_sibling->reach_sear!= true))
	 SEARCH_NODE(H,search_trav->right_sibling, key,new_key);
	    
	
    search_trav->reach_sear = false;
    //return 0;
}

void Delete_Node(fib_heap * H,int dec_key)
{ 
    node* p=NULL;
    SEARCH_NODE(H,H->min,dec_key,INT_MIN);
    //printf("%d\n",x);
    p=extract_min(H);
    //if(p!=NULL)
 	//printf("delete successfull\n");

}

int main()
{
    node *new_node, *min_node; 
    fib_heap *heap, *h1, *h2;
    int new_key, dec_key, ele, i, no_of_nodes;
    node *extracted_min, *dec_node, *search_trav;
    heap = (fib_heap *)malloc(sizeof(fib_heap));
    heap = NULL;
    char op;
    scanf("%c", &op);
    while(op!='e')
    {
    	switch(op)
        {
        

        case 'i':
        	 if(heap == NULL)
                {
                    heap = MAKE_HEAP();
                }
                
                
                scanf("%d",&ele);
                INSERT(heap,new_node,ele);
                
                break;
        
        case 'm': 
        	min_node = find_min_node(heap);
                if(min_node!=NULL)
                    printf("%d\n",min_node->key);
                break;

       
        case 'x': 
                if(heap!= NULL)
                {
                    printf("%d\n",heap->min->key);
                    extracted_min = extract_min(heap);
                    
                }
                break;

        case 'r': if(heap!= NULL)
                    
                {
                    
                    scanf("%d", &dec_key);
                    scanf("%d", &new_key);
                    search_trav = heap->min;
                    if(new_key<dec_key)
                    	SEARCH_NODE(heap,search_trav, dec_key,new_key);
                    
                    
                }
                break;
                
        case 'd':
        	if(heap!= NULL && heap->min!=NULL)
                 {
                    	scanf("%d", &dec_key);
                    	Delete_Node(heap,dec_key);
			//printf("%d\n",dec_key);
                 }
                break;
            
        case 'p': 
        	//level_order_2(heap->min); 
        	print_final(heap->min);
        	printf("\n"); 
                break;
              
        
        }
        scanf("%c", &op);
    }
    return 0;
} 
