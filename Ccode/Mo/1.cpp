#include<bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 5;
typedef long long ll;
struct Query{
    int id, l, r;
}q[maxn];
int block;
inline bool cmp(const Query &a, const Query &b){
    return (a.r / block) == (b.r / block) ? a.l < b.l : a.r < b.r;
}

// 奇偶性排序， 卡常数用， 会比原来快一倍
// inline bool cmp(const Query &a, const Query &b){
//     return (a.l / block) ^ (b.l / block) ? a.l < b.l : (((a.l / block ) & 1)? a.r < b.r : a.r > b.r);
// }

int a[maxn];
int cnt[maxn];
ll ans[maxn];

inline void add(int x, ll &res){
    ++cnt[a[x]];
    res += 2 * cnt[a[x]] - 1;
}

inline void del(int x, ll &res){
    --cnt[a[x]];
    res -= 2 * cnt[a[x]] + 1;
}

int main(){
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    block = (int)sqrt(n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < m; ++i){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q, q + m, cmp);
    memset(cnt, 0, sizeof(cnt));
    int l = 1, r = 0; //note!!!
    ll res = 0;
    for(int i = 0; i < m; ++i){
        int ql = q[i].l, qr = q[i].r;
        while(l < ql){
            del(l, res);
            ++l;
        }
        while(l > ql){
            --l; 
            add(l, res);
        }
        while(r < qr){
            ++r; 
            add(r, res);
        }
        while(r > qr){
            del(r, res); 
            --r;
        }
        ans[q[i].id] = res;
    }
    for(int i = 0; i < m; ++i){
        printf("%lld\n", ans[i]);
    }
    return 0;
}