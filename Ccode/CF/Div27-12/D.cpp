#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int a[maxn];
map<int, int>mp;
int main() {
    int n;
    while(~scanf("%d",&n)) {
        mp.clear();
        bool ok = true;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            ++mp[a[i]];
            if(mp[a[i]] >= 3) {
                ok = false;
            }
        }
        if(!ok || (mp.count(0) ? mp[0] : 0 ) >= 2) {
            puts("cslnb");
            continue ;
        }
        long long cnt = 0;
        for(auto it: mp) {
            if(it.second >= 2) {
                ++cnt;
                if(cnt >= 2) { 
                    ok = false ; break ;
                }
                if(mp.count(it.first - 1)) {
                    ok = false; break ;
                }
            }
        }
        if(!ok) {
            puts("cslnb");
            continue ;
        }
        sort(a, a + n);
        cnt = 0;
        for(int i = 0; i < n; ++i) {
            cnt += (a[i] - i);
        }
        printf("%s\n", (cnt % 2) ? "sjfnb" : "cslnb");
    }
    return 0;
}