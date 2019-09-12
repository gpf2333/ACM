#include<bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
const int mx = 27;
struct Trie{
    int ch[maxn][27], f[maxn], val[maxn], len[maxn], pos[maxn];
    int sz, rt;
    inline int idx(const char c){
        return c - 'a';
    }
    int newnode(){
        for(int i = 0; i < mx; ++i) ch[sz][i] = -1;
        return sz++;
    }
    void init(){
        for(int i = 0; i < maxn; ++i) val[i] = len[i] = 0;
        len[0] = 1;
        sz = 0, rt = newnode();
    }
    void insert(const char *s, const int id){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(!~ch[u][c]){
                ch[u][c] = newnode();
                len[ch[u][c]] = i + 1;
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
                f[ch[rt][c]] = rt;
                q.push(ch[rt][c]);
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
    void query(const char *s, const int L){
        int u = rt, tmp = u;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            u = ch[u][c];
            tmp = u;
            while(tmp != rt){
                if(len[tmp] <= L){
                    ++val[tmp];
                }
                tmp = f[tmp];
            }
        }
    }
    void show(const int q){
        for(int i = 0; i < q; ++i){
            printf("%d\n", val[pos[i]]);
        }
    }
}ac;

char s[maxn], p[maxn], temp[maxn];
const char cc = 'z' + 1;
int LL[maxn];
int main(){
    int T;
    int n, q;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        char **str = new char*[n];
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            int L = strlen(s);
            str[i] = new char[2 * L + 5];
            L = 0;
            for(int j = 0; s[j]; ++j){
                str[i][L++] = s[j];
            }
            str[i][L++] = cc;
            LL[i] = L;
            for(int j = 0; s[j]; ++j){
                str[i][L++] = s[j];
            }
            str[i][L] = '\0';
        }
        ac.init();
        for(int i = 0; i < q; ++i){
            scanf("%s%s",p, s);
            int tlen = 0;
            for(int j = 0; s[j]; ++j) temp[tlen++] = s[j];
            temp[tlen++] = cc;
            for(int j = 0; p[j]; ++j) temp[tlen++] = p[j];
            temp[tlen] = '\0';
            ac.insert(temp, i);
        }
        ac.build();
        for(int i = 0; i < n; ++i){
            ac.query(str[i], LL[i]);
        }
        ac.show(q);
        for(int i = 0; i < n; ++i){
            delete []str[i];
        }
        delete []str;
    }
    return 0;
}