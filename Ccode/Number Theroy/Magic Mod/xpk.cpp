#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 2e9;
vector<int>fac;

inline int calc(int x){
    int res = 0;
    int n = (int)fac.size();
    int up = (1 << n);
    for(int i = 1; i < up; ++i){
        int sgn = -1;
        int tmp = 1;
        for(int j = 0; j < n; ++j){
            if(i & (1 << j)){
                tmp *= fac[j];
                sgn = sgn * (-1); 
            }
        }
        res += sgn * (x / tmp);
    }
    return (x - res);
}

int main(){
    int T;
    int x, p, k, n;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &x, &p, &k);
        fac.clear();
        n = p;
        for(int i = 2; (ll)i * i <= n; ++i){
            if(n % i == 0){
                fac.push_back(i);
                while(n % i == 0){
                    n /= i;
                }
            }
        }
        if(n > 1){
            fac.push_back(n);
        }
        int ans;
        int l = 0, r = INF;
        int kk = k + calc(x);
        while(l <= r){
            int mid = (l + r) >> 1;
            if(calc(mid) >= kk){
                ans = mid, r = mid - 1;
            }else{
                l = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}