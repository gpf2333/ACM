#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;
int a[maxn];
int n, k;

bool check(int x){
    multiset<int>s;
    for(int i = 0; i < n; ++i) s.insert(a[i]);
    int cnt = 1, tmp = x;
    while(cnt <= k){
        tmp = x;
        while(tmp > 0){
            auto it = s.upper_bound(tmp);
            if(it == s.begin()) break ;
            --it;
            tmp -= *it;
            s.erase(it);
            if(s.empty()) return true;
        }
        ++cnt;
    }
    return s.empty();
}

int main(){
    int T, kase = 0;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &k);
        int sum = 0;
        for(int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
            sum += a[i];
        }
        int low = ceil((double)sum / k), ans = 0;
        for(int i = low; ; ++i){
            if(check(i)){
                ans = i; break ;
            }
        }
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}