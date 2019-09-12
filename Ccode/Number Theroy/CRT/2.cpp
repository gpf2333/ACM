#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b){
    return a / gcd(a, b) * b;
}
int main(){
    int n, k;
    ll ans = 1;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; ++i){
        int x;
        scanf("%d", &x);
        ans = lcm(ans, x) % k;
    }
    printf("%s\n", ans == 0 ? "Yes" : "No");
    return 0;
}