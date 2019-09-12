#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int mx = 26;
struct Trie{
    int ch[maxn][mx], f[maxn], pos[maxn];
    int sz, rt;
    inline int idx(const char c){
        return c - 'a';
    }
    int newnode(){
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        return sz++;
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s, int id){
        int u = rt, c;
        for(int i = 0; s[i]; ++i){
            c = idx(s[i]);
            if(!~ch[u][c]){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        pos[id] = u; 
    }
    void build(){
        queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < mx; ++c){
            if(~ch[rt][c]){
                q.push(ch[rt][c]);
                f[ch[rt][c]] = rt;
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int c = 0; c < mx; ++c){
                if(~ch[u][c]){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
}ac;

struct Edge{
    int to, next;
}edge[maxn];
int tot, head[maxn], siz[maxn];

void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1;
        siz[i] = 0;
    }
}

inline void addedge(int u, int v){
    edge[tot] = {v, head[u]};
    head[u] = tot++;
}

void dfs(int u){
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        dfs(v);
        siz[u] += siz[v];
    }
}

char s[2000050];
int main(){
    int n;
    while(~scanf("%d",&n)){
        ac.init();
        for(int i = 0; i < n; ++i){
            scanf("%s",s);
            ac.insert(s, i);
        }
        scanf("%s", s);
        ac.build();
        init(ac.sz + 1);
        int u = ac.rt;
        for(int i = 0; s[i]; ++i){
            u = ac.ch[u][ac.idx(s[i])];
            ++siz[u];
        }
        for(int i = 1; i < ac.sz; ++i){
            addedge(ac.f[i], i);
        }
        dfs(0);
        for(int i = 0; i < n; ++i){
            printf("%d\n", siz[ac.pos[i]]);
        }
    }
    return 0;
}