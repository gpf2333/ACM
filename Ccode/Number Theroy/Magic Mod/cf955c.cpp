#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const double INF = 1e18 + 5;
int calc(ll n){
    if(n <= 0) return 0;
    int l = 1, r = 1e9, ans;
    while(l <= r){
        int mid = (l + r) >> 1;
        if((ll)mid * mid <= n){
            ans = mid, l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return ans;
}
vector<ll>vec;
void init(){
    vec.clear();
    for(int i = 2; i < maxn; ++i){
        ll tmp = (ll)i * i * i;
        double t = (double)tmp;
        while(t < INF){
            int s = calc(tmp);
            if((ll)s * s != tmp) vec.push_back(tmp);
            tmp *= i;
            t *= i;
        }
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

int main(){
    init();
    int q;
    scanf("%d", &q);
    while(q--){
        ll l, r;
        scanf("%lld%lld", &l, &r);
        ll ans = upper_bound(vec.begin(), vec.end(), r) - upper_bound(vec.begin(), vec.end(), l - 1);
        ans += calc(r) - calc(l - 1);
        printf("%lld\n", ans);
    }
    return 0;
}