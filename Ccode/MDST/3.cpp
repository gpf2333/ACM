#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
#define INF 0x7f7f7f7f 
#define maxn 1111
struct node
{
    int u,v,c;
}edge[maxn*maxn];
int pre[maxn],id[maxn],vis[maxn],in[maxn],pos;
int zhuliu(int root,int n,int m)
{
    int ans=0,u,v;
    while(1)
    {
        for(int i=0;i<n;i++)in[i]=INF;
        for(int i=0;i<m;i++)
            if(edge[i].u!=edge[i].v&&edge[i].c<in[edge[i].v])
            {
                pre[edge[i].v]=edge[i].u;
                in[edge[i].v]=edge[i].c;
                if(edge[i].u==root)pos=i;
            }
        for(int i=0;i<n;i++)
            if(i!=root&&in[i]==INF) 
                return -1;
        int res=0;
        memset(vis,-1,sizeof(vis));
        memset(id,-1,sizeof(id));
        in[root]=0;
        for(int i=0;i<n;i++)
        {
            ans+=in[i];
            v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root)
            {
                vis[v]=i;
                v=pre[v];
            }
            if(id[v]==-1&&v!=root)
            {
                for(u=pre[v];u!=v;u=pre[u])
                    id[u]=res;
                id[v]=res++;
            }
        }
        if(res==0)break;
        for(int i=0;i<n;i++)
            if(id[i]==-1)
                id[i]=res++;
        for(int i=0;i<m;i++)
        {
            v=edge[i].v;
            edge[i].u=id[edge[i].u];
            edge[i].v=id[edge[i].v];
            if(edge[i].u!=edge[i].v)    
                edge[i].c-=in[v];
        }
        n=res;
        root=id[root];
    }
    return ans;
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        int sum=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].c);
            edge[i].u++,edge[i].v++,sum+=edge[i].c;
        }
        sum++;
        for(int i=0;i<n;i++)
            edge[i+m].u=0,edge[i+m].v=i+1,edge[i+m].c=sum;
        int ans=zhuliu(0,n+1,n+m);
        if(ans==-1||ans>=2*sum)printf("impossible\n");
        else printf("%d %d\n",ans-sum,pos-m);
        printf("\n");
    }
    return 0;
}