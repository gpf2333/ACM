#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 100;
const int maxm = 1e5;
struct Edge{
    int to, next;
}edge[maxm];
int tot, head[maxn];
bool vis[maxn];
int low[maxn], dfn[maxn], belong[maxn];
int index, scc;
stack<int>sta;
vector<int>G[maxn];
int in[maxn];
void init(){
    tot = 0;
    memset(head, -1, sizeof(head));
}

inline void addedge(int u, int v){
    edge[tot] = {v, head[u]};
    head[u] = tot++;
}

void dfs(int u){
    low[u] = dfn[u] = ++index;
    sta.push(u);
    vis[u] = 1;
    int v;
    for(int i = head[u]; ~i; i = edge[i].next){
        v = edge[i].to;
        if(!dfn[v]){
            dfs(v);
            if(low[u] > low[v]) low[u] = low[v];
        }else if(vis[v] && low[u] > dfn[v]){
            low[u] = dfn[v];
        }
    }
    if(low[u] == dfn[u]){
        ++scc;
        do{
            v = sta.top(); sta.pop();
            vis[v] = 0;
            belong[v] = scc;
        }while(u != v);
    }
}

void tarjian(int n){
    index = scc = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
    while(!sta.empty()) sta.pop();
    for(int i = 1; i <= n; ++i){
        if(!dfn[i]) dfs(i);
    }

    memset(in, 0, sizeof(in));
    for(int i = 0; i <= n; ++i) G[i].clear();
    for(int i = 1; i <= n; ++i){
        for(int j = head[i]; ~j; j = edge[j].next){
            int v = edge[j].to;
            if(belong[i] != belong[v]){
                ++in[belong[v]];
                G[belong[i]].push_back(belong[v]);
            }
        }
    }

}

bool bfs(){
    queue<int>q;
    for(int i = 1; i <= scc; ++i){
        if(!in[i]){
            if(!q.empty()) return false;
            q.push(i);
        }
    }
    int cnt = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = 0; i < G[u].size(); ++i){
            int v = G[u][i];
            if(--in[v] == 0){
                if(!q.empty()) return false;
                q.push(v);
            }
        }
    }
    return true;
}

int main(){
    int T, n, m, u, v;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i = 0; i < m; ++i){
            scanf("%d%d",&u,&v);
            addedge(u, v);
        }
        tarjian(n);
        if(bfs()){
            puts("I love you my love and our love save us!");
        }else{
            puts("Light my fire!");
        }
    }
    return 0;
}
