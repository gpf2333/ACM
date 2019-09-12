#include<bits/stdc++.h>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
#define Lson L,mid,lson
#define Rson mid+1,R,rson
const int maxn = 60000 + 100;
const double INF = 1e18;
double sum[maxn << 2], lazy[maxn << 2];
void pushup(int rt){
    sum[rt] = min(sum[lson], sum[rson]);
}

void pushdown(int rt){
    if(lazy[rt]){
        lazy[lson] += lazy[rt], lazy[rson] += lazy[rt];
        sum[lson] += lazy[rt], sum[rson] += lazy[rt];
        lazy[rt] = 0.0;
    }
}

void build(int L, int R, int rt, double x){
    lazy[rt] = 0;
    if(L == R){
        sum[rt] = L * x;
        return ;
    }
    int mid = (L + R) >> 1;
    build(Lson, x);
    build(Rson, x);
    pushup(rt);
}

void update(int l, int r, int val, int L, int R, int rt){
    if(l <= L && r >= R){
        lazy[rt] += val;
        sum[rt] += val;
        return ;
    }
    pushdown(rt);
    int mid = (L + R) >> 1;
    if(l <= mid) update(l, r, val, Lson);
    if(r > mid) update(l, r, val, Rson);
    pushup(rt);
}

double query(int l, int r, int L, int R, int rt){
   if(l <= L && r >= R){
       return sum[rt];
   }
   pushdown(rt);
   int mid = (L + R) >> 1;
   double res = INF;
   if(l <= mid) res = min(res, query(l, r, Lson));
   if(r > mid) res = min(res, query(l, r, Rson));
   return res;  
}

int pre[maxn], last[maxn];

bool check(int n,  double x){
    build(1, n, 1, x);
    for(int i = 1; i <= n; ++i){
        update(pre[i] + 1, i, 1, 1, n, 1);
        if(query(1, i, 1, n, 1) <= x * (1 + i)) return true; 
    }
    return false;
}

int main(){
    int T, n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i = 0; i <= n; ++i) pre[i] = last[i] = 0;
        int x;
        for(int i = 1; i <= n; ++i){
            scanf("%d",&x);
            pre[i] = last[x], last[x] = i;
        }
        double l = 0.0, r = 1.0, mid;
        //int cnt = 15;
        while((r - l) >= 1e-6){
            mid = (l + r) / 2.0;
            if(check(n, mid)) r = mid;
            else l = mid;
        }
        printf("%.4lf\n", mid);
    }
    return 0;
}