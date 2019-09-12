#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int a[maxn];
int ans[maxn];
priority_queue<int, vector<int>, greater<int> > q[maxn];
int n, k;
int calc(int mx){
    for(int i = 0; i < n; ++i){
        int t = 0,x = a[i];
        q[x].push(0);
        while(x > 0){
            ++t;
            x /= 2;
            q[x].push(t);
        }
    }
    for(int i = 0; i <= mx; ++i){
        if(q[i].size() < k){
            ans[i] = -1;
        }
        else{
            int t=k;
            while(t){
                int tt=q[i].top();q[i].pop();t--;
                ans[i]+=tt;
            }
        }
    }
    int sum = ans[0];
    for(int i = 0; i <= mx; ++i){
        if(ans[i] != -1){
            sum = min(sum, ans[i]);
        }
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    int mx = 0;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        mx = max(mx,a[i]);
    }
    cout << calc(mx) << endl;
    return 0;
}