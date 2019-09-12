#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pli pair<ll, int>
#define fir first
#define sec second
const int maxn = 1e5 + 10;
const ll inf = 2e18;
pli p1[maxn], p2[maxn];
set<pli> s;
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        s.clear();
        for(int i = 1; i <= n; i++){
            ll u, v;
            scanf("%lld%lld", &u, &v);
            p1[i].fir = u;
            p1[i].sec = i;
            p2[i].fir = v;
            p2[i].sec = i;
            s.emplace(v, i);
        }
        sort(p1 + 1, p1 + 1 + n);
        ll maxx = 0, ans = inf;
        for(int i = n; i >= 1; --i){
            int id = p1[i].sec;
            s.erase(s.find(p2[id]));
            if((int)s.size() >= 1){
                set<pli>::iterator it = s.lower_bound(p1[i]);
                if(it != s.end()){
                    ll t1 = max(maxx, it->first);
                    ans = min(ans, abs(p1[i].fir - t1));
                }
                if(it != s.begin()){
                    --it;
                    ll t2 = max(maxx, it->first);
                    ans = min(ans, abs(p1[i].fir - t2));
                }
            }
            else{
                ans = min(ans, abs(p1[i].fir - maxx));
            }
            maxx = max(p2[id].fir, maxx);
        }
        printf("%lld\n", ans);
    }
}