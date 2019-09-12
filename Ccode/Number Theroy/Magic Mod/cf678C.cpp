#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1e6 + 5;
int a[35];
vector<int> vec;
void init(){
    a[0] = 1;
    for(int i = 1; i <= 20; ++i){
        a[i] = a[i - 1] * 2;
    }
}
void calc(int n, int &res, vector<int> &vec){
    vec.clear();
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0){
            int cnt = 0;
            while(n % i == 0) n /= i, ++cnt;
            vec.push_back(cnt);
            res *= i;
        }
    }
    if(n > 1){
        vec.push_back(1);
        res *= n;
    }
}
int getval(int x){
    int l = 0, r = 20, ans;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(a[mid] >= x){
            ans = mid, r = mid - 1;
        }else{
            l = mid + 1;
        }
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    init();
    int n, res = 1;
    cin >> n;
    calc(n, res, vec);
    int ans = 0;
    if((int)vec.size() == 1){
        ans = getval(vec[0]);
        if(vec[0] != a[ans]) ++ans;
    }else{
        bool ok = 1;
        for(int i = 1; i < vec.size(); ++i){
            if(vec[i] != vec[i - 1]){
                ok = 0; break ;
            }
        }
        int mx = 1;
        for(int v: vec){
            mx = max(mx, v);
        }
        if(!ok){
            ans = 1 + getval(mx);
        }else{
            ans = getval(mx);
            if(mx != a[ans]) ++ans;
        }
    }
    cout << res << " " << ans << endl;
    return 0;
}