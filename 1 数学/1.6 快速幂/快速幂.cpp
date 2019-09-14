
typedef long long ll;
ll qpow(ll a, int b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
//10进制快速幂
ll tqpow(ll a, const char *s, const int len){
    ll res = 1;
    for(int i = len - 1; i >= 0; --i){
        if(s[i] != '0'){
            ll tmp = qpow(a, s[i] - '0');
            res = res * tmp;
        }
        a = qpow(a, 10);
    }
    return res;
}