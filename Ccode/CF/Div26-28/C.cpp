#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
char a[maxn], b[maxn];
int main(){
    scanf("%s%s",a, b);
    int lenb = strlen(b);
    int cnt = 0, ans = 0;
    for(int i = 0; b[i]; ++i){
        if(a[i] != b[i]) ++cnt;
    }
    if(!(cnt & 1)) ++ans;
    for(int i = lenb; a[i]; ++i){
        if(a[i] != a[i - lenb]) ++cnt;
        if(!(cnt & 1)) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}