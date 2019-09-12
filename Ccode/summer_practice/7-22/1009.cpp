#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int mx = 26;
char s[maxn], ans[maxn];
int n, k, tot;
int cnt[mx], las[mx];
int l[mx], r[mx];
int sum[maxn][mx], nex[maxn][mx];

inline int idx(const char c){
    return c - 'a';
}

bool check(int cur){
    if(cur == n + 1){
        for(int i = 0; i < mx; ++i){
            if(cnt[i] < l[i] || cnt[i] > r[i]) return 0; 
        }
        if(tot == k) return 1;
        return 0;n
    }
    bool ok = 1;
    ++tot, ++cnt[idx(s[cur])];
    for(int i = 0; i < mx; ++i){
        if(sum[cur + 1][i] + cnt[i] >= l[i] && cnt[i] <= r[i]) continue ;
        else{
            ok = 0; break;
        }
    }
    int tmp = 0;
    for(int i = 0; i < mx; ++i){
        tmp += std::max(l[i] - cnt[i], 0);
    }
    //note!!! two important judege
    if((k - tot > n - cur + 1) || k - tot < tmp) ok = 0;
    if(!ok){
        --tot, --cnt[idx(s[cur])];
        return 0;
    }
    return 1;
}

int main(){
    while(~scanf("%s", s + 1)){
        scanf("%d", &k);
        n = strlen(s + 1);
        for(int i = 0; i < mx; ++i){
            scanf("%d%d", &l[i], &r[i]);
            cnt[i] = 0;
            las[i] = n + 1;
            sum[n + 1][i] = 0;
        }
        for(int i = n; i; --i){
            for(int j = 0; j < mx; ++j){
                sum[i][j] = sum[i + 1][j];
                nex[i][j] = las[j];
            }
            las[idx(s[i])] = i; 
            ++sum[i][idx(s[i])];
        }
        for(int i = 0; i < mx; ++i){
            nex[0][i] = las[i];
        }
        int pos = 0;
        tot = 0;
        while(tot < k && pos <= n){
            bool ok = 1;
            for(int i = 0; i < mx; ++i){
                if(check(nex[pos][i])){
                    ans[tot] = 'a' + i;
                    pos = nex[pos][i];
                    ok = 0; break ;
                }
            }
            if(ok) break ;
        }
        if(tot != k){
            puts("-1");
        }else{
            ans[++tot] = '\0';
            puts(ans + 1);
        }
    }
    return 0;
}