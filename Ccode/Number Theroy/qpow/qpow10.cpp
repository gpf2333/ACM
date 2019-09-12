#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = (1 << 20) + 5;

char s[maxn];
int mod;
template <typename T, int N>
struct Mat{
    T a[N][N];
    Mat(){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                a[i][j] = 0;
            }
        }
    }
    void init(){
        for(int i = 0; i < N; ++i) a[i][i] = 1;
    }
    Mat operator * (const Mat& b){
        const Mat& a = *this;
        Mat c;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k){
                    c.a[i][j] = (c.a[i][j] + 1LL * a.a[i][k] * b.a[k][j] % mod) % mod;
                }
            }
        }
        return c; 
    }
    Mat qpow(ll b) const{
        Mat a = *this;
        Mat res; 
        res.init();
        while(b > 0){
            if(b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    } 
};
using mat = Mat<int, 2>;

mat qpow10(mat a, const char *s, int len){
    mat res; res.init();
    for(int i = len; i; --i){
        if(s[i] != '0'){
            res = res * (a.qpow(s[i] - '0'));
        }
        a = a.qpow(10);
    }
    return res;
}

int main(){
    int x0, x1, a, b;
    scanf("%d%d%d%d", &x0, &x1, &a, &b);
    scanf("%s%d", s + 1, &mod);
    int len = strlen(s + 1);
    if(len == 1){
        if(s[1] == '0'){
            printf("%d\n", x0 % mod); return 0;
        }else if(s[1] == '1'){
            printf("%d\n", x1 % mod); return 0;
        }else if(s[1] == '2'){
            int ans = ((ll)a * x1 % mod + (ll)b * x0 % mod) % mod;
            printf("%d\n", ans); return 0;
        }
    }
    // n = n - 1;
    for(int i = len; i; --i){
        if(s[i] == '0') s[i] = '9';
        else{
            s[i] -= 1;
            break ;
        }
    }
    mat A;
    A.a[0][0] = a, A.a[0][1] = b;
    A.a[1][0] = 1, A.a[1][1] = 0;
    mat res = qpow10(A, s, len);
    int ans = ((ll)res.a[0][0] * x1 % mod + (ll)res.a[0][1] * x0 % mod) % mod;
    printf("%d\n", ans);
    return 0;
}