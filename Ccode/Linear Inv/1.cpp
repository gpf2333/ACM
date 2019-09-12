#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;

int fac[maxn], inv[maxn], invf[maxn];
void init(){
    fac[0] = fac[1] = inv[0] = inv[1] = invf[0] = invf[1] = 1;
    for(int i = 2; i < maxn; ++i){
        fac[i] = (ll)fac[i - 1] * i % mod;
        inv[i] = (ll)(mod - mod / i) * (ll)inv[mod % i] % mod;
        invf[i] = (ll)invf[i - 1] * (ll)inv[i] % mod;
    }
}

int main(){
    init();
    return 0;
}
