#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1e6 + 10;
int fail[maxn];

void getfail(char *s, int n){
    //int  n = strlen(s);
    int i = 0, j = fail[0] = -1;
    while(i < n){
        if(j == -1 || s[i] == s[j]){
            ++i, ++j;
            if(s[i] != s[j]){
                fail[i] = j;
            }else{
                fail[i] = fail[j];
            }
        }else{
            j = fail[j];
        }
    }
}

int kmp(char *s, char *p){
    int n = strlen(s), m = strlen(p);
    int i , j, ans;
    i = j = ans = 0;
    getfail(p, m);
    while(i < n){
        if(j == -1 || s[i] == p[j]){
            ++i, ++j;
        }else{
            j = fail[j];
        }
    }
    return (2 * i - j);
}

char s[maxn], p[maxn];

int main(){
    int T, kase = 0;
    scanf("%d",&T);
    while(T--){
        scanf("%s",s);
        int n = strlen(s);
        for(int i = 0; s[i]; ++i){
            p[i] = s[n - i - 1];
        }
        p[n] = '\0';
        printf("Case %d: %d\n", ++kase, kmp(s, p));
    }
    return 0;
}