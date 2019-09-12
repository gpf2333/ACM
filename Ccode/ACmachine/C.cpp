#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 210 * 500 + 5;
bool vis[maxn];
int ans[1050];
char s[1050][55];
char str[2000050];
char ss[2000050];
struct Trie{
    int ch[maxn][128], f[maxn], id[maxn];
    int sz, rt;
    inline int idx(const char c){
        //return c - 'A';
        return c;
    }
    int newnode(){
        //memset(ch[sz], -1, sizeof(ch[sz]));
        for(int i = 0; i < 128; ++i){
            ch[sz][i] = -1;
        }
        id[sz] = -1;
        return sz++;
    }
    void init(){
        sz = 0, rt = newnode();
    }
    void insert(const char *s, const int Id){
        int u = rt;
        for(int i = 0; s[i]; ++i){
            int c = idx(s[i]);
            if(ch[u][c] == -1){
                ch[u][c] = newnode();
            }
            u = ch[u][c];
        }
        id[u] = Id;
    }
    void bulid(){
        queue<int>q;
        f[rt] = rt;
        for(int c = 0; c < 128; ++c){
            if(ch[rt][c] != -1){
                f[ch[rt][c]] = rt;
                q.push(ch[rt][c]);
            }else{
                ch[rt][c] = rt;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int c = 0; c < 128; ++c){
                if(~ch[u][c]){
                    f[ch[u][c]] = ch[f[u]][c];
                    q.push(ch[u][c]);
                }else{
                    ch[u][c] = ch[f[u]][c];
                }
            }
        }
    }
    void query(const char *s){
        int u = rt, res = 0;
        memset(ans, 0, sizeof(ans));
        for(int i = 0; s[i]; ++i){
            //if(s[i] < 'A' || s[i] > 'Z') continue ;
            int c = idx(s[i]);
            u = ch[u][c];
            int tmp = u;
            while(tmp != rt){
                if(id[tmp] != -1){
                    ++ans[id[tmp]];
                }
                tmp = f[tmp];
            }
        }
        return ;
    }
}ac;
int main(){
    int n;
    while(~scanf("%d",&n)){
        ac.init();
        for(int i = 1; i <= n; ++i){
            scanf("%s", s[i]);
            ac.insert(s[i], i);
        }
        ac.bulid();
        scanf("%s", str);
        int len = 0;
        ac.query(str);
        for(int i = 1; i <= n; ++i){
            if(ans[i]){
                printf("%s: %d\n", s[i], ans[i]);
            }
        }
    }
    return 0;
}