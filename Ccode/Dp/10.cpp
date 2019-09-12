#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int, ll>val, dp;
int n, m;
char op[15];
ll get(int x){
    return val.count(x) ? val[x] : x;
}

ll calc(int x){
    if(!x || x > n) return 0;
    if(dp.count(x)) return dp[x];
    else{
        ll res = 0;
        int ls = 0, rs = 0;
        int tmp = x;
        while(tmp <= n){
            tmp <<= 1;
            ++ls;
        }
        tmp = x;
        while(tmp <= n){
            tmp = (tmp << 1 | 1);
            ++rs;
        }
        if(ls != rs) tmp = n;
        else tmp >>= 1;
        while(tmp >= x){
            res += tmp;
            tmp >>= 1;
        }
        return res;
    }
}

void update(int pos, ll value){
    val[pos] = value;
    while(pos > 0){
        dp[pos] = max(calc(pos << 1), calc(pos << 1 | 1)) + get(pos);
        pos >>= 1;
    }
}

ll query(int x){
    ll res = get(x) + calc(x << 1) + calc(x << 1 | 1);
    ll tmp = calc(x);
    while(x > 0){
        res = max(res, tmp + calc(x ^ 1) + get(x >> 1));
        x >>= 1;
        tmp += get(x);
    }
    return res;
}

int main(){
    int u;
    ll x;
    while(~scanf("%d%d",&n,&m)){
        val.clear();
        dp.clear();
        while(m--){
            scanf("%s", op);
            if(op[0] == 'q'){
                scanf("%d", &u);
                printf("%lld\n", query(u));
            }else{
                scanf("%d%lld",&u,&x);
                update(u, x);
            }
        }
    }
    return 0;
}