#include<bits/stdc++.h>
using namespace std;

const int maxn=50005;
long long int c[maxn];
long long int sum[maxn];

struct node{
    long long int l,r,num;
}q[maxn];

long long anss[maxn];

long long int block;
long long int ans=0;

bool cmp(node a,node b){
    return (a.r/block)==(b.r/block)?a.l<b.l:a.r<b.r;
}

inline void del(int x){
    sum[c[x]]--;
    ans-=2*sum[c[x]]+1;
}

inline void add(int x){
    sum[c[x]]++;
    ans+=2*sum[c[x]]-1;
}

int main()
{
    long long int n,m,k;
    scanf("%lld%lld%lld",&n,&m,&k);
    block=sqrt(n);
    for(long long int i=1;i<=n;i++){
        scanf("%lld",&c[i]);
    }
    for(long long int i=1;i<=m;i++){
        scanf("%lld%lld",&q[i].l,&q[i].r);
        q[i].num=i;
    }
    sort(q+1,q+1+m,cmp);
    int l=1,r=0;
    for(long long int i=1;i<=m;i++){
        long long int ql=q[i].l,qr=q[i].r;
        //cout << ql << " " << qr << endl;
        while(l<ql){
            del(l);
            //printf("1 %lld ", ans);
            l++;
        }
        while(l>ql){
            l--;
            add(l);
            //printf("2 %lld ", ans);
        }
        while(r<qr){
            r++;
            add(r);
            //printf("3 %lld ", ans);
        }
        while(r>qr){
            del(r);
            r--;
            //printf("4 %lld ", ans);
        }
        //puts("");
        anss[q[i].num]=ans;
    }
    for(long long int i=1;i<=m;i++){
        printf("%lld\n",anss[i]);
    }
    return 0;
}