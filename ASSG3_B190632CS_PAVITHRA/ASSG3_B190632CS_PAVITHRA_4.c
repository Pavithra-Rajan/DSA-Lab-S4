#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct node
{
    int key, degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
}node;

node* root = NULL;

int Link(node* h1, node* h2)
{
    h1->parent = h2;
    h1->sibling = h2->child;
    h2->child = h1;
    h2->degree++;
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
       loop_tree=Q->head->key;
       DEQUEUE(Q);
        while(loop_tree!=NULL)
          {
              //printf("in while");
              printf("%d ",loop_tree->key);
              if(loop_tree->child!=NULL)
                   ENQUEUE(Q,loop_tree->child);
              loop_tree=loop_tree->sibling;
           }
    }
}

node* createNode(int n)
{
    node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->key = n;
    new_node->parent = NULL;
    new_node->sibling = NULL;
    new_node->child = NULL;
    new_node->degree = 0;
    return new_node;
}
struct node* MAKE_HEAP()
{
    struct node* head;
    head = NULL;
    return head;
}
node* MERGE(node* h1, node* h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;


    node* current = NULL;


    if (h2->degree >= h1->degree)
        current = h1;

    else if (h2->degree < h1->degree)
        current = h2;


    while (h1 != NULL && h2 != NULL)
    {

        if (h2->degree > h1->degree)
            h1 = h1->sibling;


        else if (h1->degree == h2->degree)
        {
            node* sib = h1->sibling;
            h1->sibling = h2;
            h1 = sib;
        }


        else
        {
            node* sib = h2->sibling;
            h2->sibling = h1;
            h2 = sib;
        }
    }
    return current;
}


node* UNION(node* h1, node* h2)
{
    if (h1 == NULL && h2 == NULL)
        return NULL;

    node* current = MERGE(h1, h2);


    node* prev = NULL;
    node* present = current;
    node* next = present->sibling;
    while (next != NULL)
    {
        if ((present->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == present->degree))
        {
            prev = present;
            present = next;
        }

        else
        {
            if (present->key <= next->key)
            {
                present->sibling = next->sibling;
                Link(next, present);
            }
            else
            {
                if (prev == NULL)
                    current = next;
                else
                    prev->sibling = next;
                Link(present, next);
                present = next;
            }
        }
        next = present->sibling;
    }
    return current;
}


void INSERT_aux(int x)
{

    root = UNION(root, createNode(x));
}


void level_order(node* h)
{
    while (h)
    {
        printf("%d ", h->key);
        level_order(h->sibling);
        h = h->child;
    }
}
void level_order_2(node* h)
{
    while(h!=NULL)
    { 

  
      //printf("%d ",loop_tree->key);
      //if(loop_tree->left!=NULL)
        level_order_aux(h);

        h=h->sibling;
       
     }
 //printf("\n");
}



int reverse_linked_list(node* h)
{
    if (h->sibling != NULL)
    {
        reverse_linked_list(h->sibling);
        (h->sibling)->sibling = h;
    }
    else
        root = h;
}
void min_elem(node* h)
{
    if (h == NULL)
        printf("-1");
    else
    {
        node* min_node_prev = NULL;
        node* min_node = h;

        int min = h->key;
        node* present = h;
        while (present->sibling != NULL)
        {
            if ((present->sibling)->key < min)
            {
                min = (present->sibling)->key;
                min_node_prev = present;
                min_node = present->sibling;
            }
            present = present->sibling;
        }
        printf("%d\n", min);
    }
}
int min_elem_ret(node* h)
{
    if (h == NULL)
        return -1;

    node* min_node_prev = NULL;
    node* min_node = h;

    int min = h->key;
    node* present = h;
    while (present->sibling != NULL)
    {
        if ((present->sibling)->key < min)
        {
            min = (present->sibling)->key;
            min_node_prev = present;
            min_node = present->sibling;
        }
        present = present->sibling;
    }
    return min;
}
struct node* EXTRACT_MIN(node* h)
{
    if (h == NULL)
        return NULL;

    node* min_node_prev = NULL;
    node* min_node_curr = h;
    node* next = min_node_curr->sibling;
    int min = min_elem_ret(h);
    while (next != NULL)
    {
        if (min_node_curr->key == min)
            break;
        min_node_prev = min_node_curr;
        min_node_curr = next;
        next = next->sibling;
    }
    if (min_node_prev == NULL)
        h = next;
    else
        min_node_prev->sibling = next;

    min_node_curr->sibling = NULL;
    node* temp = min_node_curr;
    min_node_curr = min_node_curr->child;
    free(temp);

    node* new = (node*)malloc(sizeof(node));

    new->parent = NULL;
    new = min_node_curr;
    min_node_prev = NULL;
    next = NULL;
    while (min_node_curr != NULL)
    {
        next = min_node_curr->sibling;
        min_node_curr->sibling = min_node_prev;
        min_node_prev = min_node_curr;
        min_node_curr = next;
    }
    new = min_node_prev;


    return UNION(h, new);

}


node* search_node(node* h, int key)
{
    if (h == NULL)
        return NULL;


    if (h->key == key)
        return h;


    node* present = search_node(h->child, key);
    if (present != NULL)
        return present;

    return search_node(h->sibling, key);
}



void DECREASE_KEY(node* H, int old_val, int new_val)
{

    node* temp = search_node(H, old_val);


    if (temp == NULL)
        return;


    temp->key = temp->key - new_val;
    node* parent = temp->parent;

    //if(temp->degree==1)
        //H=temp->sibling;
    while (parent != NULL && temp->key < parent->key)
    {
        int temp_val;
        temp_val = temp->key;
        temp->key = parent->key;
        parent->key = temp_val;
        // printf("%d\n",parent->key);
        temp = parent;
        parent = parent->parent;
    }

}

node* DELETE(node* h, int key)
{


    if (h == NULL)
    {
        printf("-1\n");
        return NULL;
     }
    node* temp = search_node(h, key);

    if (temp == NULL)
    {
        printf("-1\n");
        return h;
    }
    else
        printf("%d\n", key);

    DECREASE_KEY(h, key, 1e9);


    return EXTRACT_MIN(h);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    char op;
    int elem;
    int min;
    struct node* n;
    scanf("%c", &op);
    int dec, dec_by;
    while (op != 'e')
    {
        switch (op)
        {
        case 'i':
            scanf("%d", &elem);
            INSERT_aux(elem);
            //level_order(root);
            //printf("%d\n",root->key);
            break;
        case 'd':
            scanf("%d", &elem);
            root = DELETE(root, elem);

            break;
        case 'x':
            min_elem(root);
            root = EXTRACT_MIN(root);
            //printf("%d\n",min);
            break;
        case 'm':
            min_elem(root);
            break;
        case 'r':
            scanf("%d", &dec);
            scanf("%d", &dec_by);
            n = search_node(root, dec);
            if (n == NULL || dec < dec_by)
                printf("-1\n");
            else
            {
                DECREASE_KEY(root, dec, dec_by);
                printf("%d\n", dec - dec_by);
            }
            break;
        case 'p':
            level_order_2(root);
            printf("\n");
            break;
        }
        scanf("%c", &op);

    }
    return 0;
}
