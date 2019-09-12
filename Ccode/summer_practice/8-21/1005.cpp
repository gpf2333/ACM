#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long, int> pli;
const int maxn = 1e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
pli pa[maxn], pb[maxn];
set<pli>s;
int main(){
    int T, n;
    scanf("%d", &T);
    while(T--){
        s.clear();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i){
            ll a, b;
            scanf("%lld%lld", &a, &b);
            pa[i].first = a;
            pa[i].second = i;
            pb[i].first = b;
            pb[i].second = i;
            s.emplace(b, i);
        }
        sort(pa + 1, pa + 1 + n);
        ll ans = INF, maxx = 0;
        for(int i = n; i; --i){
            int id = pa[i].second;
            s.erase(s.find(pb[id]));
            if(s.size()){
                auto it = s.lower_bound(pa[i]);
                if(it != s.end()){
                    ll t1 = max(maxx, it->first);
                    ans = min(ans, abs(pa[i].first - t1));
                }
                if(it != s.begin()){
                    --it;
                    ll t2 = max(maxx, it->first);
                    ans = min(ans, abs(pa[i].first - t2));
                }
            }
            if(i != n){
                ans = min(ans, abs(pa[i].first - maxx));
            }
            maxx = max(maxx, pb[id].first);
        }
        printf("%lld\n", ans);
    }
    return 0;
}