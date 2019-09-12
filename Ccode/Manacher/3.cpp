#include<bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 10;
char s[maxn], temp[maxn << 1];
int p[maxn << 1];

void solve(char *s, char *temp, int *p, int &res, int &mpos){
    int n = strlen(s);
    temp[0] = '$';
    for(int i = 0; i <= n; ++i){
        temp[(i << 1) + 1] = '#';
        temp[(i << 1) + 2] = s[i];
    }
    temp[(n << 1) + 2] = '\0';
    int mx = 0, id = 0; 
    res = 1;
    n = (n << 1) + 2;
    for(int i = 2; i < n; ++i){
        if(mx > i){
            p[i] = min(p[2 * id - i], mx - i);
        }else{
            p[i] = 1;
        }
        while(temp[i - p[i]] == temp[i + p[i]]) ++p[i];
        if(mx < p[i] + i){
            id = i;
            mx = p[i] + i;
        }
        if(res < p[i] - 1){
            res = p[i] - 1;
            mpos = i;
        }
    }
}

inline char calc(const char c, int d){
    return ('a' + (((c - 'a' + d) + 26) % 26));
}

int main(){
    char tmp[10];
    while(~scanf("%s%s",tmp, s)){
        int d = 'a' - tmp[0];
        for(int i = 0; s[i]; ++i){
            s[i] = calc(s[i], d);
        }
        int res, mpos;
        solve(s, temp, p, res, mpos);
        if(res <= 1){
            puts("No solution!");
            continue ;
        }
        int st = (mpos - (res + 1)) / 2;
        int ed = st + res - 1;
        printf("%d %d\n",st, ed);
        for(int i = st; i <= ed; ++i){
            putchar(s[i]);
        }
        puts("");
    }
    return 0;
}