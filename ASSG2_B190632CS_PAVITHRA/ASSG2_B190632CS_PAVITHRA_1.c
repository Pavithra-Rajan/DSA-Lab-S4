#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct HashTable
{
	int size;
	int *table;
	int c1;
	int c2;
	char type;
}hash;

int check_prime(int n)
{
	if(n<=1)
		return 0;
	for(int i=2;i<=n/2;i++)
		if(n%i==0)
			return 0;
	return 1;
	
}
void store_prime(int primes[])
{
	
	int index=0;
	for(int i=2;i<=100;i++)
		if(check_prime(i))
		{
			primes[index]=i;
			index++;
		}
	//for(int i=0;i<25;i++)
		//printf("%d ",primes[i]);
	
}

/*int find_near_prime(int l,int r,int s,int n,int primes[])
{
	if(l<=r)
	{
		int mid=(l+r)/2;
		printf("mid=%d\n",primes[mid]);
		if(mid==0 || mid==s-1)
			return primes[mid];
		else if(primes[mid]==n)
			return primes[mid-1];
		else
		{
		if(primes[mid]<n && primes[mid+1]>n)
			return  primes[mid];
		if(n<primes[mid])
			return find_near_prime(l,mid-1,s,n,primes);
		else
			return find_near_prime(mid+1,r,s,n,primes);
		}
	}
	return 0;
			
}*/
void insert(hash* T,int k)
{
	if(T->type=='a')
		{
		int hash;
		hash=k%T->size;
		if(T->table[hash]==-1)
			T->table[hash]=k;
		else
			{
			for(int i=0;i<T->size;i++)
				{
				int hash_new=(hash+T->c1*i+T->c2*i*i)%T->size;
				if(T->table[hash_new]==-1)
					{
					T->table[hash_new]=k;
					break;
					}
				}
			}
		}
	else
	{
		int hash;
		hash=k%T->size;
		int primes[25];
		store_prime(primes);
		int R;
		for(int j=0;j<25;j++)
			if(primes[j]>=T->size)
			{
				R=primes[j-1];
				break;
			}
			
		if(T->table[hash]==-1)
			T->table[hash]=k;
		else
		{
			for(int i=0;i<T->size;i++)
			{
				
				//printf("%d is prev\n",R);
				int hash_new=(hash+i*(R-k%R))%T->size;
				if(T->table[hash_new]==-1)
					{
						T->table[hash_new]=k;
						break;
					}
					
			}
		}
	}
	
	
}

void print_table(hash *T)
{
	for(int i=0;i<T->size;i++)
		if(T->table[i]!=-1)
			printf("%d (%d)\n",i,T->table[i]);
		else
			printf("%d ()\n",i);
}
void search(hash *T,int k)
{
	int found=0;
	if(T->type=='a')
		{
		int hash;
		hash=k%T->size;
		if(T->table[hash]==k)
			found=1;
		
		else
			{
			for(int i=0;i<T->size;i++)
				{
				int hash_new=(hash+T->c1*i+T->c2*i*i)%T->size;
				if(T->table[hash_new]==k)
					{
					found=1;
					break;
					
					}
				
				}
			}
		if(found==1)
			printf("1\n");
		else
			printf("-1\n");
		}
	else
	{
		int hash;
		hash=k%T->size;
		int primes[25];
		store_prime(primes);
		int R;
		
		for(int j=0;j<25;j++)
			if(primes[j]>=T->size)
			{
				R=primes[j-1];
				break;
			}
			
		if(T->table[hash]==k)
			found=1;
		else
		{
			for(int i=0;i<T->size;i++)
			{
				
				//printf("%d is prev\n",R);
				int hash_new=(hash+i*(R-k%R))%T->size;
				if(T->table[hash_new]==k)
					{
						found=1;
						break;
					}
					
			}
		}
		if(found==1)
			printf("1\n");
		else
			printf("-1\n");
	}
	
}
void delete(hash *T,int k)
{
	
	if(T->type=='a')
		{
		int hash;
		hash=k%T->size;
		if(T->table[hash]==k)
			T->table[hash]=-1;
		
		else
			{
			for(int i=0;i<T->size;i++)
				{
				int hash_new=(hash+T->c1*i+T->c2*i*i)%T->size;
				if(T->table[hash_new]==k)
					{
					T->table[hash_new]=-1;
					break;
					
					}
				
				}
			}
		
		}
	else
	{
		int hash;
		hash=k%T->size;
		int primes[25];
		store_prime(primes);
		int R;
		
		for(int j=0;j<25;j++)
			if(primes[j]>=T->size)
			{
				R=primes[j-1];
				break;
			}
			
		if(T->table[hash]==k)
			T->table[hash]=-1;
		else
		{
			for(int i=0;i<T->size;i++)
			{
				
				//printf("%d is prev\n",R);
				int hash_new=(hash+i*(R-k%R))%T->size;
				if(T->table[hash_new]==k)
					{
						T->table[hash_new]=-1;
						break;
					}
					
			}
		}
		
	}
	
}
/*
void search(int table[],int s,int k,int c1,int c2)
{
	int hash;
	int found=0;
	hash=k%s;
	if(table[hash]==k)
		found=1;
	else
	{
		for(int i=0;i<s;i++)
		{
			int hash_new=(hash+c1*i+c2*i*i)%s;
			if(table[hash_new]==k)
				{
					found=1;
					break;
				}
		}
	}
	if(found==1)
		printf("1\n");
	else
		printf("-1\n");
}
void search2(int table[],int s,int k)
{
	int hash;
	int found=0;
	hash=k%s;
	int primes[25];
	store_prime(primes);
	int R;
	
		
	if(table[hash]==k)
		found=1;
	else
	{
		for(int j=0;j<25;j++)
			if(primes[j]>=s)
			{
				if(primes[j]==s)
					R=primes[j-1];
				else
					R=primes[j];
				break;
			}
		
		for(int i=0;i<s;i++)
		{
			
			//printf("%d is prev\n",R);
			int hash_new=(hash+i*(R-k%R))%s;
			if(table[hash_new]==k)
				{
					found=1;
					break;
				}
		}
	}
	if(found==1)
		printf("1\n");
	else
		printf("-1\n");
}
void delete(int table[],int s,int k,int c1,int c2)
{
	int hash;
	
	hash=k%s;
	if(table[hash]==k)
		table[hash]=-1;
	else
	{
		for(int i=0;i<s;i++)
		{
			int hash_new=(hash+c1*i+c2*i*i)%s;
			if(table[hash_new]==k)
				{
					table[hash_new]=-1;
					break;
				}
		}
	}
	
}
void delete2(int table[],int s,int k)
{
	int hash;
	
	hash=k%s;
	int primes[25];
	store_prime(primes);
	int R;
	
		
	if(table[hash]==k)
		table[hash]=-1;
	else
	{
		for(int j=0;j<25;j++)
		if(primes[j]>=s)
		{
			if(primes[j]==s)
				R=primes[j-1];
			else
				R=primes[j];
			break;
		}
		
		for(int i=0;i<s;i++)
		{
			
			//printf("%d is prev\n",R);
			int hash_new=(hash+i*(R-k%R))%s;
			if(table[hash_new]==k)
				{
					table[hash_new]=-1;
					break;
				}
		}
	}
	
}*/

int main()
{

	
	hash* T;
	T=(hash*)malloc(sizeof(hash));
	int ins,sear;
	
	int size;
	scanf("%c",&T->type);
	scanf("%d",&T->size);
	T->table=(int*)malloc(sizeof(int)*T->size);
	for(int i=0;i<T->size;i++)
		T->table[i]=-1;
	
	if(T->type=='a')
	{
		scanf("%d %d",&T->c1,&T->c2);
	}
	char op;
	scanf("%c",&op);
	while(op!='t')
	{ 	switch(op)
		{
		 case 'i': scanf("%d",&ins);
		 	   insert(T,ins);
		 	   break;
		 case 's': 
		           scanf("%d",&sear);
		           search(T,sear);
		 	   
		 	   break;
		 case 'p': print_table(T);
		 	   
		 	   break;
		 case 'd': scanf("%d",&sear);
		           delete(T,sear);
		 	   break;
		}
		scanf("%c",&op);
	}
		
	return 0;
}

