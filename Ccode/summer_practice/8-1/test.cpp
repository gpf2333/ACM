#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int dp[32][maxn];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    int a[35];
    while(t--){
        int m; cin >> m;
        int mx = 0;
        for(int i = 1; i <= m; ++i){
            cin >> a[i]; mx = max(a[i], mx);
        }   
        for(int i = 0; i <= m; ++i){
            for(int j = 0; j <= mx; ++j){
                dp[i][j] = 0;
            }
        }
        for(int i = 0; i <= m; ++i) dp[i][0] = 1;
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= mx; ++j){
                if(j >= a[i]){
                    dp[i][j] = dp[i - 1][j - a[i]]+dp[i-1][j];
                }
                else dp[i][j]=dp[i-1][j];
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++)
            ans+=(dp[m][a[i]]-1);
        cout << ans << endl;
    }
}