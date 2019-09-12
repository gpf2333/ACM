#include<bits/stdc++.h>
using namespace std;
#define lson rt << 1
#define rson rt << 1 | 1
#define Lson L,mid,lson
#define Rson mid+1,R,rson
typedef long long ll;
const int maxn = 1e5 + 10;
int a[maxn];
int n, c, k;

bool check(int len){
    map<int, int>mp;
    int cnt = 0;
    for(int i = 1; i <= n; ++i){
        if(a[i] <= c){
            ++mp[a[i]];
            ++cnt;
            if(cnt > len){
                --mp[a[i - len]];
                if(!mp[a[i - len]]) mp.erase(a[i - len]);
                --cnt;
            }
            if(cnt == len){
                bool ok = 1;
                for(auto it: mp){
                    if(it.second < k){
                        ok = 0;
                        break ;
                    }
                }
                if(ok) return true;
            }
        }else{
            mp.clear();
            cnt = 0;
        }
    }
    return false;
}

int main(){
    while(~scanf("%d%d%d", &n, &c, &k)){
        for(int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
        }
        int l = 1, r = n, ans, mid;
        while(l <= r){
            mid = (l + r) >> 1;
            if(check(mid)){
                ans = mid, l = mid + 1;
            }else{
                r = mid - 1;
            }
            
        }
        printf("%d\n", ans);
    }
    return 0;
}