/*
这个题最裸的暴力就是对于每个字符串，都去验证一次，时间复杂度O(n^2m)
我们发现，如果对于字符串i，前i−1个字符串都是它的子串，假如存在一个字符串j，
使得i是j的子串，那么j就不需要去验证前i−1个字符串
这样就很好想到，我们对于字符串i，
只需要记下i−1中最后一个不是它子串的字符串，就能将时间复杂度优化到O(nm)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;

//预处理模式串p
int nxt[maxn];
void initkmp(char p[], int m){
    int i = 0, j = nxt[0] = -1;
    while(i < m){
        while(j != -1 && p[i] != p[j]) j = nxt[j];
        nxt[++i] = ++j;
    }
}
//返回s中p出现的个数
int kmp(char p[], int m, char s[], int n){
    int i, j, ans;
    i = j = ans = 0;
    initkmp(p, m);
    while(i < n){
        while(j != -1 && s[i] != p[j]) j = nxt[j];
        ++i, ++j;
        if(j >= m){
            ++ans, j = nxt[j];
        }
    }
    return ans;
}   

const int mx = 500 + 5;
char s[mx][maxn];
int len[mx];
bool vis[maxn];
int main(){
    int T, cas = 0;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i){
            scanf("%s", s[i]);
            len[i] = strlen(s[i]);
            vis[i] = 1;
        }
        for(int i = 1; i < n; ++i){
            if(kmp(s[i - 1], len[i - 1], s[i], len[i]) > 0){
                vis[i - 1] = 0;
            }
        }
        printf("Case #%d: ", ++cas);
        bool ok = 0;
        for(int i = n - 1; ~i; --i){
            for(int j = 0; j < i; ++j){
                if(vis[j]){
                    if(!kmp(s[j], len[j], s[i], len[i])){
                        ok = 1;
                        printf("%d\n", i + 1);
                    }
                }
                if(ok) break ;
            }
            if(ok) break ;
        }
        if(!ok){
            printf("-1\n");
        }
    }
    return 0;
}