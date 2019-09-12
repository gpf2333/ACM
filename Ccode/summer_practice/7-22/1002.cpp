#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n, m;
int base[maxn][31], pos[maxn][31];

inline void ins(int x, int k, int r){
    for(int i = 30; ~i; --i){
        if((x >> i) & 1){
            if(!base[r][i]){
                base[r][i] = x;
                pos[r][i] = k;
                return ;
            }
            if(pos[r][i] < k){
                swap(pos[r][i], k);
                swap(base[r][i], x);
            }
            x ^= base[r][i];
        }
    }
}

inline int getmax(int l, int r){
    int ans = 0;
    for (int i = 30; ~i; i--){
        if (pos[r][i] >= l){
            ans = max(ans, ans ^ base[r][i]);
        }
    }
    return ans;
}

int main(){
    int T;
    int n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        int up = 2 * n;
        for(int i = 0; i <= up; ++i){
            for(int j = 0; j <= 30; ++j){
                base[i][j] = pos[i][j] = 0;
            }
        }
        int x;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &x);
            memcpy(base[i], base[i - 1], sizeof(base[i]));
            memcpy(pos[i], pos[i - 1], sizeof(pos[i]));
            ins(x, i, i);
        }
        int op, l, r;
        int ans = 0;
        while(m--){
            scanf("%d", &op);
            if(op){
                scanf("%d", &x);
                x = x ^ ans;
                ++n;
                memcpy(base[n], base[n - 1], sizeof(base[n]));
                memcpy(pos[n], pos[n - 1], sizeof(pos[n]));
                ins(x, n, n);
            }else{
                scanf("%d%d", &l, &r);
                l = (l ^ ans) % n + 1;
                r = (r ^ ans) % n + 1;
                if(l > r) swap(l, r);
                ans = getmax(l, r);
                printf("%d\n", ans);
            }
        }   
    }
    return 0;
}