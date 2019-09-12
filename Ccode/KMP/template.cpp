#include<bits/stdc++.h>
using namespace std;

//预处理模式串p
const int maxn = 1e5 + 5;
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

int main(){
    return 0;
}