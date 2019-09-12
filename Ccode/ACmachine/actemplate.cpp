#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 50;
struct Trie{
    int ch[maxn][26], f[maxn], val[maxn];
    int sz, rt;
    int newnode(){
        memset(ch[sz], -1, sizeof(ch[sz]));
        val[sz] = 0;
        return sz++; //note: sz++ not ++sz
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = s[i] - 'a';
            if(!~ch[u][c]){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        ++val[u];
    }
    void build(){
        std::queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < 26; ++c){
            if(~ch[rt][c]){
                f[ch[rt][c]] = rt, q.push(ch[rt][c]);
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int c = 0; c < 26; ++c){
                if(~ch[u][c]){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
    int query(const char *s){
        int u = rt, res = 0;
        for(int i = 0; s[i]; ++i){
            int c = s[i] - 'a';
            u = ch[u][c];
            int tmp = u;
            while(tmp != rt){
                res += val[tmp];
                val[tmp] = 0;
                tmp = f[tmp];
            }
        }
        return res;
    }
}ac;
char s[maxn];
int main(){
    int T, n;
    scanf("%d",&T);
    while(T--){
        ac.init();
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            ac.insert(s);
        }
        scanf("%s", s);
        ac.build();
        printf("%d\n", ac.query(s));
    }
    return 0;
}