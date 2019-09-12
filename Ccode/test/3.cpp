// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// int main(){
//     int T;
//     scanf("%d", &T);
//     while(T--){
//         int n;
//         scanf("%d", &n);
//         int m;
//         for(m = 2; (ll)m *(m - 1) / 2 <= n; ++m){;}
//         --m;
//         putchar('1');
//         for(int i = 1; i <= m - 2; ++i){
//             putchar('3');
//         }
//         int x = n - (ll)m * (m - 1) / 2;
//         for(int i = 1; i <= x; ++i){
//             putchar('1');
//         }
//         puts("337");
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
vector<char> s1, s2;
const int maxn = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int dp[maxn * 100];

int LIS(vector<int> &dp2){
    for(int i = 0; i < dp2.size() + 100; i++){
        dp[i] = INF;
    }
    for(int i = 0; i < dp2.size(); i++){
        *lower_bound(dp, dp + dp2.size(), dp2[i]) = dp2[i];
    }
    return lower_bound(dp, dp + dp2.size(), INF) - dp;
}

int solve(vector<char> &a,vector<char> &b)
{
    unordered_map<char,vector<int> >dp;
    for(int i = 0;i<a.size();++i)
    {
        if(dp.count(a[i]) == 0)
            dp[a[i]].push_back(-1);
    }
    for(int i = 0;i<b.size();++i)
    {
        if(dp.count(b[i]) == 1)
            dp[b[i]].push_back(i+1);
    }
    vector<int> dp2;
    for(int i = 0;i<a.size();++i)
    {
        if(dp[a[i]].size() > 1)
            {
                for(int j = dp[a[i]].size() - 1; j > 0; --j)
                    dp2.push_back(dp[a[i]][j]);
            }
    }
    return LIS(dp2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    string s;
    for(int i = 1; i <= 2; i++){
        cin >> s;
        for(int j = 0; s[j]; j++){
            if(i == 1) s1.push_back(s[j]);
            else{
                s2.push_back(s[j]);
            }
        }
    }
    cout << solve(s1, s2) << endl;
}
