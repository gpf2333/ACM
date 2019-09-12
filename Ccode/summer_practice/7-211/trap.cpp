#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
bool isprime[maxn];
int cntp, prime[maxn], mu[maxn];
vector<vector<int> >vec(maxn), p(maxn);

void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    cntp = 0, mu[1] = 1;
    p.clear(); p.resize(maxn);
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    for(int i = 1; i < maxn; ++i){
        for(int j = i; j < maxn; j += i){
            p[j].push_back(i);
        }
    }
}

int cnt[maxn];
int main(){
    init();
    int n;
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        vec.clear();
        vec.resize(maxn);
        int x, mx;
        for(int i = 0; i < n; ++i){
            scanf("%d", &x);
            ++cnt[x];
            mx = max(mx, x);
            for(int j: p[x]){
                vec[j].push_back(x);
            }
        }
        ll ans = 0;
        for(int i = 1; i <= mx; ++i){
            if(!mu[i] || vec[i].empty()) continue ;
            ll tmp = 0;
            sort(vec[i].begin(), vec[i].end());
            vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
            int siz = vec[i].size();
            for(int j = 0; j < siz; ++j){
                int x = vec[i][j];
                int l = j, r = j;
                if(l < siz) ++l;
                if(l == siz) break ;
                for(int k = 0; k < siz; ++k){
                    int y = vec[i][k], z = x + 2 * y;
                    if(cnt[y] < 2) continue ;
                    while(r < siz - 1 && vec[i][r + 1] < z) ++r;
                    if(x != y){
                        tmp += r - l + 1;                    
                        if(cnt[y] < 3 && vec[i][l] <= y && y <= vec[i][r]) --tmp;
                    }else if(x == y && cnt[y] >= 3){
                        tmp += r - l + 1; 
                    }
                }
            }
            ans += tmp * mu[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
