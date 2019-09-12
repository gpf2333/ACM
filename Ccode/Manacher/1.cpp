#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1e6 + 5;
/*
T(n) = O(n)
加完特殊字符后，朌长子串的长度是半径减1，起始位置是中间位置减去半径再除以2。
 */
struct Manacher{
    char s[maxn], temp[maxn << 1];
    int p[maxn << 1];
    void init(char *s, char *temp){
        int n = strlen(s);
        temp[0] = '$';
        for(int i = 0; i <= n; ++i){
            temp[(i << 1) + 1] = '#';
            temp[(i << 1) + 2] = s[i];
        }
        temp[(n << 1) + 2] = '\0';
    }
    void getlen(char *s, int *p){
        int mx = 0, id = 0;
        int n = strlen(s);
        p[0] = 0;
        for(int i = 2; i < n; ++i){
            if(mx > i){
                p[i] = min(p[2 * id - i], mx - i);
            } else {
                p[i] = 1;
            }
            while(s[i - p[i]] == s[i + p[i]]){
                ++p[i];
            }
            if(mx < p[i] + i){
                id = i;
                mx = p[i] + i;
            }
        }
    }
}ma;
int main(){
    int kase = 0;
    while(~scanf("%s", ma.s)){
        if(ma.s[0] == 'E'){
            break ;
        }
        ma.init(ma.s, ma.temp);
        ma.getlen(ma.temp, ma.p);
        int n = strlen(ma.temp);
        int ans = 1;
        for(int i = 2; i < n; ++i){
            ans = max(ans, ma.p[i] - 1);
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}