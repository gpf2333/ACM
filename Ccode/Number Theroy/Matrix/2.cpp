#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

const int N = 10;
struct mat{
    int v[N][N];
    mat(){
        std::memset(v, 0, sizeof(v));
    }
    void clear(){
        std::memset(v, 0, sizeof(v));
    }
    void init(){
        for(int i = 0; i < N; ++i) v[i][i] = 1;
    }
    int* operator[](int x){
        return v[x];
    }
    const int* operator[](int x) const{
        return v[x];
    }
    mat operator*(const mat&b){
        const mat& a = *this;
        mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    c[i][j] = (c[i][j] + (ll)a[i][k] * b[k][j] % mod) % mod;
                }
            }
        }
        return c;
    }
    mat qpow(ll b) const{
        mat a = *this, res;
        res.init();
        while(b > 0){
            if(b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
};

int main(){
    ll n;
    mat A, F;
    for(int i = 0; i < 10; ++i){
        if(i == 0){
            for(int j = 0; j < 3; ++j) A[i][j] = 1;
        }else if(i == 1){
            for(int j = 0; j < 4; ++j) A[i][j] = 1;
        }else if(i == 8){
            for(int j = 6; j < 10; ++j) A[i][j] = 1;
        }else if(i == 9){
            for(int j = 7; j < 10; ++j) A[i][j] = 1;
        }else{
            for(int j = i - 2; j <= i + 2; ++j) A[i][j] = 1;
        }
    }
    while(~scanf("%lld", &n)){
        if(n == 1){
            puts("10"); continue ;
        }else{
            mat res = A.qpow(n - 1);
            F.clear();
            for(int i = 1; i < 10; ++i){
                F[i][0] = 1;
            }
            F = res * F;
            int ans = 0;
            for(int i = 0; i < 10; ++i){
                ans = (ans + F[i][0]) % mod;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}