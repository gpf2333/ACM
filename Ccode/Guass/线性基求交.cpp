#include<bits/stdc++.h>
using namespace std;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L, mid, lson
#define Rson mid + 1, R, rson
typedef long long ll;
const int maxn = 50000 + 10;

const int mx = 32;
struct LinerBase{
    ll base[mx + 1];
    int rk;
    LinerBase(){
        memset(base, 0, sizeof(base));
        rk = 0;
    }

    bool insert(ll x){
        for(int i = mx; ~i; --i){
            if(x & (1LL << i)){
                if(!base[i]){
                    base[i] = x;
                    ++rk;
                    break ;
                }
                x ^= base[i];
            }
        }
        return x > 0;
    }

    bool find(ll x){
        if(!rk) return 0;
        for(int i = mx; ~i; --i){
            if(x & (1LL << i)){
                if(base[i]){
                    x ^= base[i];
                    if(!x) return 1;
                }else{
                    return 0;
                }
            }
        }
        return 1;
    }
};

LinerBase Merge(const LinerBase &a, const LinerBase &b){
    LinerBase all, c, d;
    for(int i = mx; ~i; --i){
        all.base[i] = a.base[i];
        d.base[i] = 1LL << i;
    }
    for(int i = 0; i <= mx; ++i){
        if(b.base[i]){
            ll v = b.base[i], k = 0;
            bool can = 1;
            for(int j = mx; ~j; --j){
                if((v >> j) & 1){
                    if(all.base[j]){
                        v ^= all.base[j];
                        k ^= d.base[j];
                    }else{
                        can = 0;
                        all.base[j] = v;
                        d.base[j] = k;
                        break ;
                    }
                }
            }
            if(can){
                ll v = 0;
                for(int j = mx; ~j; --j){
                    if((k >> j) & 1){
                        v ^= a.base[j];
                    }
                }
                c.insert(v);
            }
        }
    }
    return c;
}


LinerBase lb[maxn];
LinerBase tree[maxn << 2];

void pushup(int rt){
    tree[rt] = Merge(tree[lson], tree[rson]);
}

void build(int L, int R, int rt){
    if(L == R){
        tree[rt] = lb[L];
        return ;
    }
    int mid = (L + R) >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

bool query(int l, int r, ll x, int L, int R, int rt){
    if(l <= L && r >= R){
        return tree[rt].find(x);
    }
    int mid = (L + R) >> 1;
    bool ok1 = 1, ok2 = 1;
    if(l <= mid) ok1 = query(l, r, x, Lson);
    if(r > mid) ok2 = query(l, r, x, Rson);
    return (ok1 && ok2);
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    ll x;
    for(int i = 1; i <= n; ++i){
        int k;
        scanf("%d", &k);
        while(k--){
            scanf("%lld", &x);
            lb[i].insert(x);
        }
    }
    build(1, n, 1);
    int l, r;
    while(m--){
        scanf("%d%d%lld", &l, &r, &x);
        bool ok = query(l, r, x, 1, n, 1);
        printf("%s\n", ok ?"YES":"NO");
    }
    return 0;
}