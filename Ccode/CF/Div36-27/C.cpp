#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int q;
    int k, n, a, b;
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d%d",&k,&n,&a,&b);
        int tmp = (k - 1) / b;
        if(tmp >= n){
            ll ans = (ll)(k - (ll)b * n - 1LL) / (a - b);
            ans = min(ans, (ll)n);
            printf("%I64d\n", ans);
        }else{
            puts("-1");
        }
    }
    return 0;
}