#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 505;
ll len[maxn];
vector<string> v;
string s1 = "COFFEE";
string s2 = "CHICKEN";
void dfs(int n, ll k, int l){
    if(k + l > len[n]){
        l = len[n] - k + 1;
    }
    if(n == 1){
        //cout << n << " " << k << " " << l << endl;
        if(l == 0)
        {
            return;
        }
        for(int i = 0; i < l; i++){
            cout << s1[i + k - 1];
        }
        return;
    }
    if(n == 2){
        //cout << n << " " << k << " " << l << endl;
        if(l == 0){
            return;
        }
        for(int i = 0; i < l; i++){
            //cout << i + k - 1 << endl;
            cout << s2[i + k - 1];
        }
        return;
    }
    if(n - 2 >= 56){
        dfs(n - 2, k, 10);
    }
    else if(len[n - 2] >= k + 10LL){
        dfs(n - 2, k, 10);
    }
    else if(len[n - 2] >= k && len[n - 2] < k + 10LL){
        dfs(n - 2, k, len[n - 2] - k + 1);
        dfs(n - 1, 1, 10 - len[n - 2] + k - 1);
    }
    else if(len[n - 2] < k){
        dfs(n - 1, k - len[n - 2], min(10LL, len[n - 1] - (k - len[n - 2]) + 1));
    }
    return ;
}

int main()
{
    len[1] = 6LL;
    len[2] = 7LL;
    for(int i = 3; i <= 56; i++){
        len[i] = len[i - 2] + len[i - 1];
    }
    int t;
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> t;
    while(t--){
        int n;
        ll k;
        v.clear();
        cin >> n >> k;
        dfs(n, k, 10);
        cout << endl;
    }
}