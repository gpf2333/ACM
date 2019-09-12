#include<bits/stdc++.h>
using namespace std;
const int maxn = 2050;
int a[maxn];
int dp[maxn][maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    cin >> a[1];
    int d = a[1];
    for(int i = 2; i <= n; i++){
        cin >> a[i];
        d = __gcd(d, a[i]);
    }
    if(d != 1){
        cout << "-1" << endl;
        return 0;
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(a[i] == 1) cnt++;
    }
    if(cnt){
        cout << n - cnt << endl;
        return 0;
    }
    for(int i = 1; i <= n; i++){
        dp[i][i] = a[i];
        for(int j = i + 1; j <= n; j++){
            dp[i][j] = __gcd(dp[i][j - 1], a[j]);
        }
    }
    int minn = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            if(dp[i][j] == 1)
                minn = min(minn, j - i);
        }
    }
    cout << minn + (n - 1) << endl;
    return 0;
}