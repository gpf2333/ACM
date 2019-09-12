#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=905;
vector<int> G[maxn],query[maxn];
int ans[maxn],fa[maxn];
bool vis[maxn],in[maxn];
int n,m;
void init(){
    for(int i=1;i<=n;i++){
        G[i].clear();query[i].clear();
        fa[i]=i;in[i]=0;ans[i]=0;vis[i]=0;
    }
}
int find(int x){
    return fa[x]==x?x:find(fa[x]);
}
void add_edge(int u,int v){G[u].push_back(v);}
void add_query(int u,int v){query[u].push_back(v);}
void Tarjan(int u){
    vis[u]=1;int size=query[u].size();
    for(int i=0;i<size;i++){
        int v=query[u][i];
        if(vis[v]) ans[find(v)]++;
    }
    size=G[u].size();
    for(int i=0;i<size;i++){
        int v=G[u][i];
        if(!vis[v]){
            Tarjan(v);fa[v]=u;
        }
    }
}
int main()
{
    while(~scanf("%d",&n)){
        init();
        int u,v;
        for(int i=0;i<n;i++){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);in[v]=1;
                add_edge(u,v);add_edge(v,u);
            }
        }
        scanf("%d",&m);
        while(m--){
            scanf(" (%d %d)",&u,&v);
            add_query(u,v);add_query(v,u);
        }
        for(int i=1;i<=n;i++)
            if(!in[i]){
                Tarjan(i);break;
            }
        for(int i=1;i<=n;i++)
            if(ans[i]) printf("%d:%d\n",i,ans[i]);
    }
}