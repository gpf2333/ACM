#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int mod = 100000;
const int maxn = 100 + 5;
const int mx = 4;
struct Trie{
    int ch[maxn][mx], f[maxn];
    bool val[maxn];
    int sz, rt;
    inline int idx(const char c){
        if(c == 'A') return 0;
        if(c == 'C') return 1;
        if(c == 'T') return 2;
        return 3;
    }
    int newnode(){
        //memset(ch[sz], -1, sizeof(ch[sz]));
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        val[sz] = 0;
        return sz++;
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(!~ch[u][c]){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        val[u] = 1;
    }
    void build(){
        queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < mx; ++c){
            if(~ch[rt][c]){
                f[ch[rt][c]] = rt;
                q.push(ch[rt][c]);
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(val[f[u]]){
                val[u] = 1; // note!
            }
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

char s[maxn];
int N;
struct mat{
    int a[maxn][maxn];
    void clear(){
        memset(a, 0, sizeof(a));
    }
    void init(){
        memset(a, 0, sizeof(a));
        for(int i = 0; i < maxn; ++i) a[i][i] = 1;
    }
    mat operator * (const mat b) const {
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                c.a[i][j] = 0;
                for(int k = 0; k < N; ++k){
                    c.a[i][j] = (c.a[i][j] + (ll)a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return c;
    }
};

mat fast_pow(mat a, int b){
    mat res;
    res.init();
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main(){
    int n, m;
    while(~scanf("%d%d",&m,&n)){
        ac.init();
        for(int i = 0; i < m; ++i){
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build();
        N = ac.sz;
        mat a;
        a.clear();
        for(int i = 0; i < ac.sz; ++i){
            for(int j = 0; j < mx; ++j){
                if(!ac.val[i] && !ac.val[ac.ch[i][j]]){
                    ++a.a[i][ac.ch[i][j]];
                }
            }
        }
        a = fast_pow(a, n);
        int ans = 0;
        for(int i = 0; i < N; ++i){
            ans = (ans + a.a[0][i]) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}