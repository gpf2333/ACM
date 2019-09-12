#include<bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 5;
const int up = 50000;
bitset<maxn>a, b, ans, bs;
int main(){
    int t,n, m, q;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&m,&q);
        a.reset(), b.reset(), ans.reset(),bs.reset();
        int x;
        for(int i = 1; i <= n; ++i){
            scanf("%d",&x);
            a.set(x);
        }
        int maxx = 0;
        for(int i = 1; i <= m; ++i){
            scanf("%d",&x);
            b.set(x);
            maxx = max(x, maxx);
        }
        for(int i = maxx; i >= 0; --i){
            ans[i] = ((a >> i) & bs).count() & 1;
            if(b[i]){
                for(int j = 0; j <= maxx; j += i){
                    bs.flip(j);
                }
            }
        }
        while(q--){
            scanf("%d",&x);
            if(ans[x]){
                puts("1");
            }else{
                puts("0");
            }
        }
    }
    return 0;
}