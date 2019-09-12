#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

ll fast_pow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    
    return 0;
}