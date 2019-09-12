#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

char get(int tmp){
    if(tmp == 1) return 'A';
    if(tmp == 3) return 'B';
    if(tmp == 2) return 'C';
    return 'D';
}

int main(){
    int n;
    scanf("%d",&n);
    int ans = 0;
    char c = get(n % 4);
    char cc = get((n + 1) % 4);
    char ccc = get((n + 2) % 4);
    if(c < cc && c < ccc){
        printf("0 %c\n", c);
    }else if(cc < c && cc < ccc){
        printf("1 %c\n", cc);
    }else if(ccc < c && ccc < c){
        printf("2 %c\n", ccc);
    }
    return 0;
}