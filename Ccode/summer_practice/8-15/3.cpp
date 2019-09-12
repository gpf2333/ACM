#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __int128_t i128;
const int maxn=1e5+5;
int fa[maxn],rnk[maxn],sum[maxn];
int tot,cnt[maxn];
int sum2=0,sum3=0,sum4=0,sum5=0;

void init(int n){
    for(int i=1;i<=n;i++){
        fa[i]=i;rnk[i]=0;sum[i]=1;
    }
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

bool merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return 0;
    if(rnk[x]<rnk[y]) {fa[x]=y;sum[y]+=sum[x];}
    else{
        fa[y]=x;
        if(rnk[x]==rnk[y]) rnk[x]++;
        sum[x]+=sum[y];
    }
    return 1;
}
 
set<int> s;
ull ans;
 
ull solve(ull n){
    ull t=0,par=0,tt=0;
    for(auto &v:s){
        if(v >= 2){
            //cout<<(n-v)<<" -> "<<cnt[v]<<endl;
            if(n - v >= 2) t += (ull)(n - v) * (n - v - 1) / 2 * cnt[v] * ((ull) v * (v - 1) /2);
            tt += (ull)v * (v - 1) / 2 * cnt[v];
        }
        if(v >= 3){
            //cout<<(n-v)<<" -> "<<cnt[v]<<endl;
            if(n - v >= 1) t += (ull)v * (v - 1) *(v - 2) / 6 * (ull)cnt[v] * (n - v);
        }
        if(v >= 4){
            //cout<<(n-v)<<" -> "<<cnt[v]<<endl;
            t += ((ull)v * (v-1) / 2) * (v - 2) / 3 * (v - 3) / 4 * cnt[v];
        }
         
    }
    for(auto &v:s){
        if(v >= 2){
            par += ((ull)v * (v - 1) / 2) *(tt - (ull)v * (v - 1) / 2) * cnt[v];
        }
        //cout<<tt<<" x "<<v*(v-1)/2<<endl;}
    }
    //par=sum2*(sum2-1)/2;
    par/=2;
    //cout<<t<<" "<<par<<endl;
    return t-par;
}
 
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    ull t = n;
    ans = t * (t - 1) / 2 * (t - 2) / 3 * (t - 3) / 4;
    cout<<ans<<endl;
    init(n);
    sum2=0;
    sum3=0;
    s.insert(1);
    cnt[1]=n;sum5=n;sum4=0;
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        int s1 = sum[find(x)], s2 = sum[find(y)];
        cnt[s1]--;cnt[s2]--;
        if(cnt[s1]<=0) s.erase(s1);
        if(cnt[s2]<=0) s.erase(s2);
        if(s1>=2) sum2--;if(s2>=2) sum2--;
        if(s1>=3) sum3--;if(s2>=3) sum3--;
        if(s1>=4) sum4--;if(s2>=4) sum4--;
        bool sta=merge(x,y);
        if(sta==1){
            int r=find(x);
            cnt[sum[r]]++;sum5--;
            s.insert(sum[r]);
            if(sum[r]>=2) sum2++;
            if(sum[r]>=3) sum3++;
            if(sum[r]>=4) sum4++;
        }
        if(sum5 < 4){
            cout << 0 << endl;
            continue;
        }
        cout << ans - solve(n) << endl;
    }
    return 0;
}
 