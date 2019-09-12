#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a)) 
typedef long long ll;
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=1e6+5;
ll a[maxn],b[maxn],c[maxn];
ll sum1=0,sum2=0,sum3=0;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n;cin>>n;
        sum1=0;sum2=0;sum3=0;
        for(int i=0;i<n;i++){
            cin >> a[i] >> b[i];
            sum1 += a[i]; sum2 += b[i];
        }
        for(int i=0;i<n;i++){
            c[i]=min(b[i],sum2-b[i]);
            if(c[i]>a[i]){
                sum3+=c[i]-a[i];c[i]=a[i];
            }
            else if(c[i]<a[i]){
                if(sum3>=a[i]-c[i]){
                    sum3-=a[i]-c[i];c[i]=a[i];
                    //cout<<a[i]-c[i]<<"+"<<sum3<<endl;
                }
                else if(sum3>0){
                    c[i]+=sum3;sum3=0;
                }
            }
            if(b[i]>c[i]) sum3+=b[i]-c[i];
        }
        ll ans=0;
        //for(int i=0;i<n;i++) cout<<c[i]<<" ";cout<<endl;
        //cout<<sum3<<endl;
        if(sum3>0){
            for(int i=0;i<n;i++){
                if(sum2-b[i]<=b[i]) continue;
                if(c[i]<a[i]){
                    if(sum3>=a[i]-c[i]){c[i]=a[i];sum3-=a[i]-c[i];}
                    else if(sum3>0) {c[i]+=sum3;sum3=0;}
                }
                if(sum3==0) break;
            }
        }
/*         for(int i=0;i<n;i++){
            if(a[i]>c[i]){
                if(sum3>=a[i]-c[i]){
                    c[i]=a[i];sum3-=a[i]-c[i];
                }
                else if(sum3>0){
                    c[i]+=sum3;sum3=0;
                }
            }
            ans+=c[i];
        } */
        //for(int i=0;i<n;i++) cout<<c[i]<<" ";cout<<endl;
        for(int i=0;i<n;i++) ans+=c[i];
        cout<<ans<<endl;
    }
}

/*
1
3
3 1
3 5
3 0
*/