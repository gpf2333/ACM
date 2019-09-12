#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 100;
int n;

ll gcd(ll x, ll y){
    return !y ? x : gcd(y, x % y);
}

ll a[maxn];
int solve(){
    ll res = a[0];
    for(int i = 1; i < n; i++){
        res = gcd(res,a[i]);
    }
    if(res == 1){
        return 1;
    }
    int ans = 0;
    for(ll i = 1; i * i <= res; ++i){
        if(!(res % i) && i * i!= res){
            ans += 2;
        }
        else if(res % i == 0){
            ++ans;
        }
    }
    return ans; 
};

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%lld", &a[i]);
    }
    printf("%d\n", solve());
}