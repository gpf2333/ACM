#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n, k;
    scanf("%I64d%I64d", &n, &k);
    ll ans =((ll)sqrt(9 + 8 * (n + k)) + (-3)) / 2;
    ans = abs(n - ans);
    printf("%I64d\n", ans);
    return 0;
}