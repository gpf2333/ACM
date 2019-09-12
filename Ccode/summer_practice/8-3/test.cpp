#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n, k;
    while(~scanf("%d%d", &n, &k)){
        ll ans = (ll)n * k;
        ll tmp = 0;
        for(int l = 1, r; l <= n; l = r + 1){
            if(k / l == 0){
                r = n;
            }else{
                r = min(n, k / (k / l));
            }
            ll t = (ll)(l + r) * (r - l + 1) / 2;
            tmp += (k / l) * t;
        }
        ans -= tmp;
        printf("%lld\n", ans);
    }
    return 0;
}