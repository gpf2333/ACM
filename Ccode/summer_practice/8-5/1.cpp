#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
int nxt[maxn],ext[maxn];
void pre_ekmp(string a,int m){
    nxt[0]=m;int j=0;
    while(j+1<m&&a[j]==a[j+1]) j++;
    nxt[1]=j;int k=1;
    for(int i=2;i<m;i++){
        int p=nxt[k]+k-1;int l=nxt[i-k];
        if(i+l<p+1) nxt[i]=l;
        else{
            j=max(0,p-i+1);
            while(i+j<m&&a[i+j]==a[j]) j++;
            nxt[i]=j;k=i;
        }
    }
}
void ekmp(string a,int m,string b,int n){
    pre_ekmp(a,m);
    int j=0;while(j<n&&j<m&&a[j]==b[j]) j++;
    ext[0]=j;int k=0;
    for(int i=1;i<n;i++){
        int p=ext[k]+k-1;int l=nxt[i-k];
        if(i+l<p+1) ext[i]=l;
        else{
            j=max(0,p-i+1);
            while(i+j<n&&j<m&&b[i+j]==a[j]) j++;
            ext[i]=j,k=i;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s,t;cin>>s;t=s;
        int len=s.length();
        if(len<=1){cout<<0<<endl;continue;}
        ekmp(s,len,t,len);
        ll ans=0;
        for(int i=1;i<len;i++){
            if(ext[i]>0&&ext[i]+i<len) ans++;
            if(ext[i]==0) ans++;
            else ans=ans+(ll)ext[i];
        }
        cout<<ans<<endl;
    }

}