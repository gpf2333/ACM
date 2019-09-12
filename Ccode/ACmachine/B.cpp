#include<bits/stdc++.h>
using namespace std;
const int mx = 128;
const int maxn = 500 * mx;
struct Trie{
    int ch[maxn][mx], f[maxn], val[maxn];
    int sz, rt;
    inline int idx(const char c){
        return c;
    }
    int newnode(){
        for(int i = 0; i < mx; ++i){
            ch[sz][i] = -1;
        }
        val[sz] = -1;
        return sz++;
    }
    int init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s, const int id){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(ch[u][c] == -1){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        val[u] = id;
    }
    void build(){
        queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < mx; ++c){
            if(ch[rt][c] != -1){
                f[ch[rt][c]] = rt;
                q.push(ch[rt][c]);
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int c = 0; c < mx; ++c){
                if(ch[u][c] != -1){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
    int query(const char *s, int n, bool vis[]){
        int u = rt, res = 0;
        for(int i = 0; i <= n; ++i){
            vis[i] = 0;
        }
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            u = ch[u][c];
            int tmp = u;
            while(tmp != rt){
                if(val[tmp] != -1){
                    vis[val[tmp]] = 1;
                    res = 1;
                }
                tmp = f[tmp];
            }
        }
        return res;
    }
}ac;
char s[10050];
bool vis[maxn];
int main(){
    int n, m;
    while(scanf("%d",&n) != EOF){
        ac.init();
        for(int i = 1; i <= n; ++i){
            scanf("%s", s);
            ac.insert(s, i);
        }
        ac.build();
        scanf("%d",&m);
        int sum = 0;
        for(int i = 1; i <= m; ++i){
            scanf("%s",s);
            if(ac.query(s, n, vis)){
                ++sum;
                printf("web %d:", i);
                for(int j = 1; j <= n; ++j){
                    if(vis[j]){
                        printf(" %d", j);
                    }
                }
                putchar('\n');
            }
        }
        printf("total: %d\n", sum);
    }
}