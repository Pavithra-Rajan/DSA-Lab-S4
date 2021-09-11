#include<stdio.h>

void DFS(int);
int G[10][10],num_ver,dfs_visit[10],ver_index[20],bfs_visit[20],forw=0,back=-1;

void BFS(int v)
{
    int i,j;
    for (i=0; i<num_ver; i++)
        if(!bfs_visit[i] && G[v][i])
            ver_index[++back]=i;
    if(forw<=back)
    {
        bfs_visit[ver_index[forw]]=1;
        BFS(ver_index[forw++]);
    }
}
void DFS(int v)
{
    int i;
    printf("%d ",v);
    dfs_visit[v]=1;
    for(i=0; i<num_ver; i++)
    {
        if(!dfs_visit[i]&&G[v][i]==1)
        {
            DFS(i);
        }
        else;
    }
}

int main()
{
    int i,j;
    int e,u,v,start;
    //printf("Vertices and edges:");
    scanf("%d",&num_ver);
    scanf("%d",&e);
    //printf("Adj Mat");
    for(i=0; i<num_ver; i++)
    {
        for(j=0; j<num_ver; j++)
        {
            G[i][j]=0;
        }
    }
    for(i=0;i<e;i++)
    	{
    		scanf("%d",&u);
    		scanf("%d",&v);
    		G[u][v]=1;
    	}
    

    for(i=0; i<num_ver; i++)
    {
        dfs_visit[i]=0;
    }
    
    for (i=0; i<num_ver; i++)
    {
        ver_index[i]=0;
        bfs_visit[i]=0;
    }
    scanf("%d",&start);
    
    BFS(start);
    
    printf("%d ",start);
    for (i=0; i<num_ver; i++)
     	if(bfs_visit[i] && i!=start)
        	printf("%d ",i);
        
        
    printf("\n");
    DFS(start);
    printf("\n");
    return 0;
}


