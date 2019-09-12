#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 50;
const int mod = 1e9 + 7;
const int base = 26;
char s[maxn];
struct Node{
    int id,len;
    int a[maxn];
}cnt[27];

bool cmp(const Node &a, const Node &b){
    if(a.len > b.len) return true;
    else if(a.len < b.len) return false;
    for(int i = a.len - 1; i >= 0; --i){
        if(a.a[i] > b.a[i]) return true;
        else if(a.a[i] < b.a[i]) return false;
        else continue;
    }
    return false;
}

ll pw[maxn];
void init(){
    pw[0] = 1;
    for(int i = 1; i < maxn; ++i){
        pw[i] = pw[i - 1] * base % mod;
    }
}

bool head[30];

int main(){
    init();
    int n;
    int kase = 0;
    while(~scanf("%d", &n)){
        for(int i = 0; i < 26; ++i){
            cnt[i].id = i;
            cnt[i].len = 0;
            memset(cnt[i].a, 0, sizeof(cnt[i].a));
            head[i] = 0;
        }
        int x;
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            int len = strlen(s);
            if(len > 1) head[s[0] - 'a'] = 1;
            for(int j = 0, k = len - 1; j < k; ++j, --k){
                swap(s[j], s[k]);
            }
            for(int j = 0; s[j]; ++j){
                x = s[j] - 'a';
                ++cnt[x].a[j];
                cnt[x].len = max(cnt[x].len, j + 1);
            }
        }

        for(int i = 0; i < 26; ++i){
            for(int j = 0; j < cnt[i].len; ++j){
                x = cnt[i].a[j] / base;
                if(x){
                    if(j == (cnt[i].len - 1)){
                        ++cnt[i].len;
                    }
                    cnt[i].a[j + 1] += x;
                }
                cnt[i].a[j] %= base;
            }
        }

        sort(cnt, cnt + 26, cmp);
        ll num = 25, ans = 0;
        int pos = -1;
        if(head[cnt[25].id]){
            for(int i = 25; i >= 0; --i){
                if(head[cnt[i].id] == false){
                    pos = i;
                    break ;
                }
            }
        }
        for(int i = 0; i < 26; ++i){
            if(cnt[i].len > 0 && i != pos){
                ll tmp = 0;
                for(int j = 0; j < cnt[i].len; ++j){
                    if(cnt[i].a[j]){
                        tmp = (tmp + cnt[i].a[j] * pw[j] % mod) % mod;
                    }
                }
                ans = (ans + num * tmp % mod) % mod;
                --num;
            }
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
    return 0;
}
