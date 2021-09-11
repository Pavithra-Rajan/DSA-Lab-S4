#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//KRUS
typedef struct node_krus
{
	int key;
	int weight;
	struct node_krus *next;
}node_krus;

typedef struct krus_ver
{
	int u;
	int v;
	int weight;
	struct krus_ver *next;
}krus_ver;


typedef struct sing_node  // each node
{
	int key;
	int rep;
	int weight;
	char colour;
}sing_node;

//PRIM
typedef struct Edge
{
	int u,v,w;
}Edge;

typedef struct vertices
{
	int ver1,ver2;
} vert;

Edge Adj_Mat[1000][1000];
int num_vert,visited[1000],size[1000];
vert Heap[1000];
int Heap_ind[1000],Heapsize;

//KRUS FUNC
krus_ver *CREATE_KRUS_NODE(int u, int v, int weight)
{
	krus_ver *new_node = (krus_ver*)malloc(sizeof(krus_ver));
	new_node->u = u;
	new_node->v = v;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}

krus_ver* PRI_INSERT_Krus(krus_ver *node_k, int u, int v, int weight)
{
	if(node_k == NULL)
	{
		krus_ver *new_node = CREATE_KRUS_NODE(u, v, weight);
		return new_node;
	}
	else
	{
		if(node_k->weight <= weight)
		{
			node_k->next = PRI_INSERT_Krus(node_k->next, u, v, weight);
			return node_k;
			
		}
		else
		{
			krus_ver *new_node = CREATE_KRUS_NODE(u, v, weight);
			new_node->next = node_k;
			return new_node;
		}
	}
}

struct GRAPH_K
{
	int Num_of_Ver;
	sing_node *vertex;
	struct node_krus **Adj_List_krus;
};

struct GRAPH_K* Krus_Graph_Create(int Num_of_Ver)
{
	struct GRAPH_K *g = (struct GRAPH_K*)malloc(sizeof(struct GRAPH_K));
	g->Num_of_Ver = Num_of_Ver;
	g->Adj_List_krus = malloc(Num_of_Ver * sizeof(struct node_krus*));
	g->vertex = malloc(Num_of_Ver * sizeof(sing_node));
	int i;
	for( i = 0; i < Num_of_Ver; i++)
	{
		g->Adj_List_krus[i] = NULL;
		g->vertex[i].colour = 'w';
		g->vertex[i].rep = -1;
		g->vertex[i].key = i;
		g->vertex[i].weight = INT_MAX;
	}
	return g;
}


struct node_krus* Create_Adj_List_K(int key)
{
	if(key == -1)
		return NULL;
	else
	{
		struct node_krus *new_k_node = (struct node_krus *)malloc(sizeof(struct node_krus));
		new_k_node->key = key;
		new_k_node->weight = 0;
		new_k_node->next = NULL;
		return new_k_node;
	}
}

struct node_krus* Krus_Insert_Adj(struct node_krus *vert1, struct node_krus *vert2)
{
	if(vert1 == NULL)
		return vert2;
	else
	{
		vert1->next = Krus_Insert_Adj(vert1->next, vert2);
		return vert1;
	}
}

int Rep_Ret(struct GRAPH_K *g, int u)
{
	return g->vertex[u].rep;
}

struct GRAPH_K* Set_Union_krus(struct GRAPH_K *g, int u, int v)
{
	int i;
	for(i = 0; i < g->Num_of_Ver; i++)
		if(g->vertex[i].rep == v)
			g->vertex[i].rep = u;
	return g;
}

long int Krus_Min_Span(struct GRAPH_K *g)
{
	int i, u, v;
	krus_ver *node_k = NULL;
	long int Krus_sum = 0;
	for(i = 0; i < g->Num_of_Ver; i++)
	{
		g->vertex[i].weight = INT_MAX;
		g->vertex[i].colour = 'w';
		g->vertex[i].rep = i;
		struct node_krus *present = g->Adj_List_krus[i];
		while(present != NULL)
		{
			node_k = PRI_INSERT_Krus(node_k, i, present->key, present->weight);
			present = present->next;
		}
	}
	
	while(node_k != NULL)
	{
		u = node_k->u;
		v = node_k->v;
		if(Rep_Ret(g, u) != Rep_Ret(g, v))
		{
			Krus_sum += node_k->weight;
			g = Set_Union_krus(g, Rep_Ret(g, u), Rep_Ret(g, v));
		}
		node_k = node_k->next;
	}
	return Krus_sum;
}

//PRIM FUNC
int right(int u)
{
	return 2*u+2;
}

int left(int u)
{
	return 2*u+1;
}

int parent(int u)
{
	return (u-1)/2;
}


vert min_val()
{
	return Heap[0];
}




void swap_vert(vert *a,vert *b)
{
	vert temp = *a;
	*a = *b;
	*b = temp;
	int tt = Heap_ind[a->ver2];
	Heap_ind[a->ver2] = Heap_ind[b->ver2];
	Heap_ind[b->ver2] = tt;
}

void INSERT(vert x)
{
	Heap[Heapsize] = x;
	Heap_ind[x.ver2] = Heapsize;	
	int  i = Heapsize;
	Heapsize++;
	while(i!=0 && Heap[parent(i)].ver1 > Heap[i].ver1)
	{
		swap_vert(&Heap[parent(i)],&Heap[i]);
		i = parent(i);
	}
}

void DECREASE(int x,int w)
{
	int i = Heap_ind[x];
	if(Heap[i].ver1 > w)
	{
		Heap[i].ver1 = w;
		while(i!=0 && Heap[parent(i)].ver1 > Heap[i].ver1)
		{
			swap_vert(&Heap[parent(i)],&Heap[i]);
			i = parent(i);
		}
	}
}

void MinHeapify(int i) 
{ 
    int smallest = i;
    int r = right(i); 
    int l = left(i); 
         
    if (Heap[l].ver1 < Heap[i].ver1 && l < Heapsize) 
        smallest = l; 
    if (Heap[r].ver1 < Heap[smallest].ver1 && r < Heapsize) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap_vert(&Heap[i], &Heap[smallest]); 
        MinHeapify(smallest); 
    } 
} 

struct vertices EXTRACT_MIN() 
{ 
    vert root = Heap[0]; 
    if (Heapsize <= 0) 
        return root; 
    if (Heapsize == 1) 
    { 
        Heapsize--; 
        return Heap[0]; 
    } 
  
    Heap[0] = Heap[Heapsize-1]; 
    Heapsize--; 
    MinHeapify(0);   
    return root; 
} 
  

int main()
{
	char option;
	scanf("%c",&option);
	if(option=='a')
	{
		int n, i, key, digit, neg;
		scanf("%d", &n);
		struct GRAPH_K *g = Krus_Graph_Create(n);	
		digit = getchar();
		for(i = 0; i < n; i++)
		{
			struct node_krus *reach_ver = NULL;
			key = -1;
			while(1)
			{
				digit = getchar();
				if(digit == 10)
				{
					reach_ver = Create_Adj_List_K(key);
					g->Adj_List_krus[i] = Krus_Insert_Adj(g->Adj_List_krus[i], reach_ver);
					break;
				}
				else if(digit == ' ')
				{
					reach_ver = Create_Adj_List_K(key);
					g->Adj_List_krus[i] = Krus_Insert_Adj(g->Adj_List_krus[i], reach_ver);
					key = -1;
					neg = 1;
				}
				else
				{
					if(key == -1)
						key = 0;
					key = key * 10 + ( (int)digit - 48 );
				}
			}
		}
		for(i = 0; i < n; i++)
		{
			struct node_krus *present = g->Adj_List_krus[i];
			key = -99999;
			neg = 1;
			while(1)
			{
				digit = getchar();
				if(digit == 10)
				{
					if(key != -99999)
						present->weight = neg * key;
					neg = 1;
					break;
				}
				else if(digit == '-')
					neg = -1;
					
				else if(digit == ' ')
				{
					present->weight = neg * key;
					key = -99999;
					neg = 1;
					present = present->next;
				}
				
				else
				{
					if(key == -99999)
						key = 0;
					key = key * 10 + ( (int)digit - 48 );
				}
			}
		}
		long int Krus_sum = Krus_Min_Span(g);
		printf("%ld\n", Krus_sum);
	}
	if(option=='b')
	{
		scanf("%d",&num_vert);
		char digit = '\0';
		digit = getchar();
		for(int i=0;i<num_vert;++i)
		{
			digit = getchar();
			if(digit=='\n') 
				continue;
			int value = digit - '0';
			while(digit!='\n')
			{
				digit = getchar();
				if(digit == '\n' || digit == ' ')
				{
					Adj_Mat[i][size[i]].v = value;
					Adj_Mat[i][size[i]].u = i;
					size[i]++;
					//printf("the val: %d\n",value);
					value = 0;
				}
				else 
					value = value*10 + digit - '0';			
			}
		}
		for(int i=0;i<num_vert;++i)
			for(int j=0;j<size[i];++j)
			{
				int w;
				scanf("%d",&w);
				Adj_Mat[i][j].w = w;;
			}	
		vert temp ;
		long long PRIM_MIN_SPAN = 0;
		temp.ver1 = 0;
		temp.ver2 = 0;	
		INSERT(temp);
		for(int i=1;i<num_vert;++i)
		{
			temp.ver2 = i;
			temp.ver1 = INT_MAX;
			INSERT(temp);
		}
		while(Heapsize)
		{
			temp = min_val();
			EXTRACT_MIN();
			
			if(visited[temp.ver2]) 
				continue;
			visited[temp.ver2] = 1;
			PRIM_MIN_SPAN += temp.ver1;
			for(int i=0;i<size[temp.ver2];++i)
			{
				Edge x = Adj_Mat[temp.ver2][i]; 
				
				if(!visited[x.v]) DECREASE(x.v,x.w);
			}
		}
		printf("%lld\n",PRIM_MIN_SPAN);
	}
	return 0;
}
