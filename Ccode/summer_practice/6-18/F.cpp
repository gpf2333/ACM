#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
bool vis[maxn];
int a[maxn], b[maxn];
int loopa[maxn], loopb[maxn];

int main(){
    int n, m, kase = 0;
    while(~scanf("%d%d",&n,&m)){
        for(int i = 0; i < n; ++i){
            scanf("%d",&a[i]);
        }
        for(int i = 0; i < m; ++i){
            scanf("%d",&b[i]);
        }
        for(int i = 0; i < n; ++i){
            vis[i] = 0;
        }
        int cnta = 0;
        for(int i = 0; i < n; ++i){
            if(!vis[i]){
                vis[i] = 1;
                loopa[cnta] = 1;
                int nex = a[i];
                while(nex != i){
                    vis[nex] = 1;
                    nex = a[nex];
                    ++loopa[cnta];
                }
                ++cnta;
            }
        }
        for(int i = 0; i < m; ++i){
            vis[i] = 0;
        }
        int cntb = 0;
        for(int i = 0; i < m; ++i){
            if(!vis[i]){
                vis[i] = 1;
                loopb[cntb] = 1;
                int nex = b[i];
                while(nex != i){
                    vis[nex] = 1;
                    nex = b[nex];
                    ++loopb[cntb];
                }
                ++cntb;
            }
        }
        ll ans = 1;
        for(int i = 0; i < cnta; ++i){
            ll tmp = 0;
            for(int j = 0; j < cntb; ++j){
                if(loopa[i] % loopb[j] == 0){
                    tmp = (tmp + loopb[j]) % mod;
                }
            }
            ans = (ans * tmp) % mod;
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
}