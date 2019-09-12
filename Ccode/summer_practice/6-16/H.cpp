#include<bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 3000;
char s[maxn];
int k;
long long a[30], b[30];
long long c[30];
bool checkup(const char c){
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}
bool checknum(const char c){
    if(c >= '0' && c <= '9') return true;
    return false;
}
void getinit(char *s, long long *a){
    memset(a, 0, sizeof(a));
    long long num = 0;
    bool ok = true;
    char c = a[0];
    int n = strlen(s);
    for(int i = 0; i < n; ++i){
        if(checkup(s[i]) && ( (i + 1 < n && checkup(s[i + 1]) ) || i == n - 1)){
            ++a[s[i] - 'A'];
        } else if(checkup(s[i]) && ( i + 1 < n &&checknum(s[i + 1]))){
            c = s[i];
        } else if(checknum(s[i]) && ((i + 1 < n && checkup(s[i + 1]) ) || i == n - 1)){
            num = num * 10 + (s[i] - '0');
            a[c - 'A'] += num;
            num = 0;
        } else{
            num = num * 10 + (s[i] - '0');
        }
    }
}
int main(){
    scanf("%s%d",s, &k);
    getinit(s, a);
    scanf("%s",s);
    getinit(s, b);
    memset(c, 0, sizeof(c));
    for(int i = 0; i < 30; ++i){
        if(a[i] && b[i]){
            //cout << a[i] << " " << b[i] << endl;
            c[i] = (1LL * a[i] * k) / b[i];
        }
    }
    long long maxx = inf;
    for(int i = 0; i < 30; ++i){
        if(b[i]){
            maxx = min(c[i], maxx);
        }
    }
    if(maxx == inf){
        cout << 0 << endl;
    } else{
        cout << maxx << endl;
    }
    return 0;
}
