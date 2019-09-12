#include<bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;

int a[maxn], b[maxn];
struct PrimerTree{
    struct Node{
        int ls, rs, sum;
    }tree[maxn * 40]; //32 or 40
    int ct;
    int sz; // 
    int rt[maxn * 40];

    inline void cpy(int&now, int old){
        now = ++ct;
        tree[now] = tree[old];
    }

    inline void pushup(const int& now){
        tree[now].sum = tree[tree[now].ls].sum + tree[tree[now].rs].sum;
    }

    void build(int&now, int L, int R){
        now = ++ct;
        tree[now].sum = 0;
        if(L == R) return ;
        int mid = (L + R) >> 1;
        build(tree[now].ls, L, mid);
        build(tree[now].rs, mid + 1, R);
    }

    void update(int &now, int old, int L, int R, int val){
        cpy(now, old);
        if(L == R){
            ++tree[now].sum;
            return ;
        }    
        int mid = (L + R) >> 1;
        if(val <= mid) update(tree[now].ls, tree[old].ls, L, mid, val);
        else update(tree[now].rs, tree[old].rs, mid + 1, R, val);
        pushup(now);
    }

    int query_tree(int u, int v, int lca, int lca_fa, int L, int R, int k){
        if(L >= R) return L;
        int mid = (L + R) >> 1;
        int cnt = tree[tree[u].ls].sum + tree[tree[v].ls].sum - tree[tree[lca].ls].sum - tree[tree[lca_fa].ls].sum;
        if(k <= cnt) return query_tree(tree[u].ls, tree[v].ls, tree[lca].ls, tree[lca_fa].ls, L, mid, k);
        return query_tree(tree[u].rs, tree[v].rs, tree[lca].rs, tree[lca_fa].rs, mid + 1, R, k - cnt);
    }

    void init(int n){
        ct = 0;
        build(rt[0], 1, n);
    }

    void Hash(int n, int a[], int b[]){
        for(int i = 1; i <= n; ++i) b[i] = a[i];
        sort(b + 1, b + n + 1);
        sz = unique(b + 1, b + n + 1) - (b + 1);
        init(sz);
        for(int i = 1; i <= n; ++i){
            a[i] = lower_bound(b + 1, b + sz + 1, a[i]) - b;
        }
    }

    int Query_tree(int u, int v, int lca, int lca_fa, int k){
        return query_tree(rt[u], rt[v], rt[lca], rt[lca_fa], 1, sz, k);
    }

}pt;


struct Edge{
    int to, next, w;      
}edge[maxn << 1];

int tot, head[maxn];
int dfs_clock;
int siz[maxn], top[maxn], son[maxn], dep[maxn], fa[maxn], id[maxn];

void init(int n){
    tot = dfs_clock = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1;
        son[i] = -1;
    }
}

inline void addedge(int u, int v, int w = 0){
    edge[tot] = {v, head[u], w};
    head[u] = tot++;
}

//求出重儿子，轻儿子
void dfs1(int u, int pa, int d){
    dep[u] = d, fa[u] = pa, siz[u] = 1;
    pt.update(pt.rt[u], pt.rt[fa[u]], 1, pt.sz, a[u]); // father update son, important
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == pa) continue ;
        dfs1(v, u, d + 1);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[v] > siz[son[u]]){
            son[u] = v;
        }
    }
}

//求出轻重链
void dfs2(int u, int t){
    top[u] = t, id[u] = ++dfs_clock;
    if(son[u] == -1) return ;
    dfs2(son[u], t);
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v != son[u] && v != fa[u]){
            dfs2(v, v);
        }
    }
}

int getlca(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    return x;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    pt.Hash(n, a, b);
    init(n);
    for(int i = 1; i < n; ++i){
        int u, v, w;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    int ans = 0;
    while(m--){
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        u = u ^ ans;
        int z = getlca(u, v);
        ans = b[pt.Query_tree(u, v, z, fa[z], k)];
        printf("%d\n", ans);
    }
    return 0;
}