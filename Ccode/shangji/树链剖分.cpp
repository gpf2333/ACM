// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int maxn  = 1e5 + 10;
// struct Edge{
//     int from, to, next;
// }edge[maxn << 2];
// int tot, head[maxn];

// void init(){
//     tot = 0;
//     memset(head, -1, sizeof(head));
// }

// inline void addedge(const int u, const int v){
//     edge[tot].from = u;
//     edge[tot].to = v;
//     edge[tot].next = head[u];
//     head[u] = tot++;
// }

// int pre[maxn]; // father of u
// int dep[maxn]; // deepth of u
// int siz[maxn]; // size of root(u)
// int son[maxn]; // heavery of u
// int pos[maxn];  // dfs
// int top[maxn];  // 
// int id;

// void dfs1(int u, int fa, int d){
//     dep[u] = d;
//     pre[u] = fa;
//     son[u] = -1;
//     for(int i = head[u]; ~i; i = edge[i].next){
//         if(edge[i].to = fa) continue ;
//         dfs(edge[i].to, u, d + 1);
//         siz[u] += siz[edge[i].to];
//         if(son[u] == -1 || siz[son[u]] < siz[edge[i].to]){
//             son[u] = edge[i].to;
//         }
//     }
// }

// void dfs2(int u, int t){
//     top[u] = t;
//     pos[u] = ++id;
//     if(son[u] == -1) return ;
//     dfs2(son[u], t);
//     for(int i = head[u]; ~i; i = edge[i].next){
//         if(edge[i].to == pre[u] || edge[i].to == son[u]) continue ;
//         dfs2(edge[i].to, edge[i].to);
//     }
// }

// int main(){
//     int n, q;
//     while(~scanf("%d%d", &n, &q)){
//         init();
//         int u, v;
//         for(int i = 1; i < n; ++i){
//             scanf("%d%d", &u, &v);
//             addedge(u, v);
//             addedge(v, u);
//         }
//         dfs1(1, -1, 1);
//         id = 0;
//         dfs2(1, 1);
//     }
//     return 0;
// }