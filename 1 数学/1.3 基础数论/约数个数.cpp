

/*
sqrt(n)内求出一个数的约数个数
*/
typedef long long ll;
ll calc(ll n){
    ll res = 0;
    for(ll l = 1, r;  l <= n; l = r + 1){
        r = n / (n / l);
        res += n / l * (r - l + 1);
    }
    return res;
}