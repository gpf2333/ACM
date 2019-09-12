#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b); 
}

ll qpow(ll a, ll b, const int mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    return 0;
}