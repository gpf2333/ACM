#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2500 + 100;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
char a[maxn], b[maxn];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s%s",a,b);
        int lena = strlen(a), lenb = strlen(b);
        if(lena > lenb){
            for(int i = 0, j = 0; i < lena; ++i){
                if(a[i] == b[j]) continue ;
                else{
                    if(a[i] == '.'){
                        
                    }
                }
            }
        }
    }
    return 0;
}