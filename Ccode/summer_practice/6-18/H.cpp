#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 10;
struct Node{
    int id, val;
    bool operator < (const Node &b) const {
        return val < b.val;
    }

}b[110];

unsigned ans[110];
unsigned a[maxn];
int n, m, A, B, C;
unsigned x, y, z;
unsigned rng61() {
    unsigned t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

int main(){
    ios::sync_with_stdio(false);
    int kase = 0;
    while(~scanf("%d%d%d%d%d",&n, &m,&A,&B,&C)){
        for(int i = 0; i < m; ++i){
            scanf("%d", &b[i].val);
            b[i].id = i;
        }
        x = A, y = B, z = C;
        for(int i = 0; i < n; ++i){
            a[i] = rng61();
        }
        sort(b, b + m);
        b[m].val = n;
        for(int i = m - 1; i >= 0; --i){
            nth_element(a, a + b[i].val, a + b[i + 1].val);
            ans[b[i].id] = a[b[i].val];
        }
        printf("Case #%d:", ++kase);
        for(int i = 0; i < m; ++i){
            printf(" %u", ans[i]);
        }
        puts("");
    }
    return 0;
}