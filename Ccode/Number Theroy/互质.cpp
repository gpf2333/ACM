#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 100;

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int a[maxn];                                                                                                                                                                                                                                       
int main(){
    int n, k;
    while(~scanf("%d%d", &n, &k)){
        int cnt = 0;
        for(int i = 1; i <= n; ++i){
            if(gcd(i, n) == 1){
                a[++cnt] = i;
            }
        }
        ll ans = (ll)(k - 1) / cnt * (ll)n + a[(k - 1) % cnt + 1];
        printf("%lld\n", ans);
    }    
    return 0;
}