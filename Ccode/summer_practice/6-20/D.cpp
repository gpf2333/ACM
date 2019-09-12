#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
typedef long long ll;
struct Node{
    int id, val;
    bool operator < (const Node &b) const{
        return val < b.val;
    }
}a[maxn];

int c[maxn];
bool vis[maxn];
int maxx = maxn;
void add(int i, int val){
    while(i <= maxx){
        c[i] += val;
        i += i & (-i);
    }
}

ll getsum(int i){
    ll res = 0;
    while(i > 0){
        res +=  c[i];
        i -= i & (-i);
    }
    return res;
}

int main(){
    int T, n, m, p;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d", &n,&m,&p);
        int up = n * m - 1;
        maxx = up;
        for(int i = 0; i <= up; ++i){
            vis[i] = 0;
            c[i] = 0;
        }
        int cnt = 1;
        for(int i = 1; i <= up; ++i){
            int tmp = i;
            while(tmp <= up && !vis[tmp]){
                vis[tmp] = 1;
                a[cnt].val = tmp;
                a[cnt].id = cnt;
                ++cnt;
                tmp += p;
            }
        }
//        for(int i = 1; i <= up; ++i){
//            printf("%d ",a[i].val);
//        }
//        puts("");
        sort(a + 1, a + up + 1);
        ll res = 0;
        for(int i = 1; i <= up; ++i){
            add(a[i].id, 1);
            res += (i - getsum(a[i].id));
        }
        cout << res << endl;
        bool ok = true;
        if(res & 1 == 0){
            ok = true;
        }else{
            ok = false;
        }
        if(ok){
            puts("YES");
        }else{
            puts("NO");
        }
    }
    return 0;
}

