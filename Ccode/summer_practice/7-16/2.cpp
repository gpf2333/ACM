#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
int b[maxn];
multiset<int>a;
multiset<int>c1, c2;
int main(){
    int T, n, m, kase = 0;
    scanf("%d",&T);
    while(T--){
        a.clear(); c1.clear(); c2.clear();
        scanf("%d%d", &n, &m);
        int x;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &x);
            a.insert(x);
        }
        for(int i = 1; i <= m; ++i){
            scanf("%d", &b[i]);
        }
        for(int i = 1; i <= m; ++i){
            scanf("%d", &x);
            if(x) c2.insert(b[i]);
            else c1.insert(b[i]);
        }
        ll tmp1 = 0, tmp2 = 0;
        multiset<int>::reverse_iterator rit = a.rbegin();
        for(auto it = c1.begin(); it != c1.end() && rit != a.rend(); ++it, ++rit){
            if(*rit > *it){
                tmp1 += (*rit - *it);
            }else{
                break ;
            }
        }
        if(c2.size()){
            for(auto it = lower_bound(a.begin(), a.end(), *c2.begin()), itt = c2.begin(); it != a.end() && itt != c2.end(); ){
                if(*it >= *itt){
                    a.erase(it);
                    c2.erase(itt);
                    ++it; 
                    itt = c2.begin();
                }else{
                    ++it;
                }
            }
            rit = a.rbegin();
            int c = 0;
            for(auto it = c1.begin(); it != c1.end() && rit != a.rend(); ++it, ++rit){
                if(*rit > *it){
                    tmp2 += (*rit - *it);
                    ++c;
                }else{
                    break ;
                }
            }
            if(c >= c1.size() && c2.size() == 0){
                int cc = 0, up = a.size() - c1.size();
                for(auto it = a.begin(); it != a.end(); ++it){
                    if(cc < up){
                        tmp2 += *it; ++cc;
                    }else{
                        break ;
                    }   
                }
            }
        }
        ll ans = max(tmp1, tmp2);
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}