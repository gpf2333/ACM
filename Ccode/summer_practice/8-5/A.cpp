#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void ex(ll b, ll a, ll d, ll c, ll &x, ll &y){
    ll p1 = b / a, p2 = d / c;
    if(p1 != p2){
        y = 1, x = p1 + 1;
        return ;
    }
    b -= a * p1;
    d -= c * p2;
    ex(c, d, a, b, y, x);
    x += y * p1;
}

int main(){
    ll p, a;
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld", &p, &a);
        ll x, y;
        ex(p, a, p, a - 1, x, y);
        ll ans = x * a - p * y;
        printf("%lld/%lld\n", ans, x);
    }
    return 0;
}