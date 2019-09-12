#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t;
    ll n, m;
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld",&n,&m);
        if(n == 1){
            puts("0");
            continue ;
        }
        ll d = n * (n -  1LL) / 2;
        if(m >= d){
            ll ans = n * (n - 1);
            printf("%lld\n", ans);
        }else if(m >= n){
            ll ans = n * (n - 1) + 2LL * (d - m);
            printf("%lld\n", ans);
        }else{
            ll ans = 2LL * m * m + n * (n - (m + 1)) * (n + m);
            printf("%lld\n", ans);
        }
    }
    return 0;
}