#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn = 30;
const int mx = 26;
struct Trie{
    int ch[maxn][mx], f[maxn];
    bool val[maxn];
    int sz, rt;
    inline int idx(const char c){
        return (c - 'a');
    }
    int newnode(){
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
            if(ch[u][c] == -1){
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
                val[u] = 1;
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
int N;
struct mat{
    ull a[maxn][maxn];
    void clear(){
        memset(a, 0, sizeof(a));
    }
    void init(){
        memset(a, 0, sizeof(a));
        for(int i = 0; i < maxn; ++i) a[i][i] = 1;
    }
    mat operator * (const mat &b) const {
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                c.a[i][j] = 0;
                for(int k = 0; k < N; ++k){
                    c.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }
        return c;
    }
};

mat fast_pow(mat a, long long b){
    mat res; res.init();
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

char s[maxn];
int main(){
    int n, L;
    while(~scanf("%d%d",&n,&L)){
        ac.init();
        for(int i = 0; i < n; ++i){
            scanf("%s",s);
            ac.insert(s);
        }
        ac.build();

        mat a;
        a.clear();
        N = ac.sz + 1;
        for(int i = 0; i < ac.sz; ++i){
            if(ac.val[i]) continue;
            for(int j = 0; j < mx; ++j){
                if(!ac.val[ac.ch[i][j]]){
                    ++a.a[i][ac.ch[i][j]];
                }
            }
        }
        for(int i = 0; i <= ac.sz; ++i){
            a.a[i][ac.sz] = 1;
        }

        a = fast_pow(a, L);
        ull tmp = 0;
        for(int i = 0; i < N; ++i){
            tmp = (tmp + a.a[0][i]);
        }

        N = 2;
        a.clear();
        a.a[0][0] = 1, a.a[0][1] = 26;
        a.a[1][0] = 0, a.a[1][1] = 26;
        a = fast_pow(a, L - 1);
        ull sum = (a.a[0][0] + a.a[0][1]) * (ull)26;
        ull ans = sum - tmp + 1;
        printf("%llu\n", ans); 
    }
    return 0;
}