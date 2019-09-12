#include<bits/stdc++.h>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
#define Lson L,mid,lson
#define Rson mid+1,R,rson
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 250000 + 50;
int a[maxn * 4];
int b[maxn];
int sum[maxn * 8];
char op[10];
int n,m;
void pushup(int rt)
{
    sum[rt] = max(sum[lson], sum[rson]);
}
int cnt = 0;
void build(int L,int R,int rt)
{
    if(L == R)
    {
        if(cnt < n){
            scanf("%d", &a[++cnt]);
            sum[rt] = a[cnt] - cnt;
        }
        else{
            sum[rt] = 0;
            //a[++cnt] = 0;
        }
        return ;
    }
    int mid = (L+R)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}
void update(int l,int r,int val,int L,int R,int rt)
{
    if(l<=L && r >= R)
    {
        sum[rt] = val;
        return ;
    }
    int mid = (L+R)>>1;
    if(l<=mid)
     update(l,r,val,Lson);
    if(r>mid)
       update(l,r,val,Rson);
    pushup(rt);
}
int query(int l, int r,int L,int R,int rt)
{
    if(l<=L&&r>=R)
    {
        return sum[rt];
    }
    int mid=(L+R)>>1;
    int res = 0;
    if(l <= mid)
      res = max(res,query(l,r,Lson));
    if(r > mid)
      res = max(res,query(l,r,Rson));
    return res;
}
int main(){
    while(~scanf("%d",&n)){
        int up = n * 2;
        build(1, up, 1);
        for(int j = 1; j <= n; ++j){
            scanf("%d",&b[j]);
        }
        sort(b + 1, b + n + 1);
        ll ans = 0;
        for(int i = 1; i <= n; ++i){
            //cout << b[i] << " " << i + n - 1 << " ";
            a[i + n] = query(b[i], i + n - 1, 1, up, 1);
            //cout << a[i + 1] << " ";
            update(i + n, i + n, a[i + n] - i - n, 1, up, 1);
            ans = ((ans + a[i + n]) % mod + mod) % mod;
        }
        puts("");
        printf("%lld\n", ans);
    }
    return 0;
}

/*
4
8 11 8 5
3 1 4 2
*/
