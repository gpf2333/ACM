#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int fail[maxn];
void getfail(char *x){
    int m = strlen(x);
    int i = 0, j = fail[0] = -1;
    while(i < m){
        while(j != - 1 && x[i] != x[j]) j = fail[j];
        fail[++i] = ++j;
    }
}

int kmp(char *x, char *y){
    int i, j, ans;
    i = j = ans = 0;
    //getfail(x);
    int m = strlen(x);
    int n = strlen(y);
    while(i < n){
        while(j != - 1 && y[i] != x[j]){
            j = fail[j];
        }
        ++i, ++j;
        ans = max(ans, j);
    }
    return ans;
}
char s[maxn];
int Len[maxn];
int main(){
    int T, n, m, x, y;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        char **str = new char*[n + 2];
        for(int i = 1; i <= n; ++i){
            scanf("%s", s);
            int len = strlen(s);
            Len[i] = len;
            str[i] = new char[len + 2];
            for(int j = 0; s[j]; ++j){
                str[i][j] = s[j];
            }
            str[i][len] = '\0'; 
        }
        scanf("%d",&m);
        int tmp = 0, ans = 0;;
        while(m--){
            scanf("%d%d",&x, &y);
            ans = 0;
            for(int i = 1; i <= n; ++i){
                string p = "";
                int len = min(Len[x], Len[y]);
                getfail(str[i]);
                for(int j = 0; j < Len[i]; ++j){
                    p += str[i][j];
                    int tmp = min(kmp(str[i], str[x]), kmp(str[i], str[y]));
                    tmp = min(tmp, (int)p.size());
                    ans = max(ans, tmp);
                    if(ans < (int)p.size()) break ;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}