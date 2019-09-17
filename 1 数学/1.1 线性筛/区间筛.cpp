// ---
// 对区间$[a,b)$内的整数执行筛法。\\
// 函数返回区间内素数个数\\
// \texttt{is\_prime[i-a]=true}表示$i$是素数\\
// $1<a<b \le 10^{12}, b-a \le 10^6$
// ---
typedef long long ll;
const int maxn = 1e6 + 10;
const int N = 50000; // sqrt(2^31) 46340
bool isprime[maxn]; //2 ~ sqrt(R)
bool isprime_big[maxn];
//pre
void init(){
    for(int i = 2; i < N; ++i) isprime[i] = 1;
    for(int i = 2; i * i < N; ++i){
        if(isprime[i]){
            for(int j = 2 * i; j < N; j += i){
                isprime[j] = 0;
            }
        }
    }
}

void solve(ll L,ll R){
    int len = R - L + 1;
    for(int i = 0; i < len; ++i) isprime_big[i] = 1;
    if(L == 1) isprime_big[0] = 0;
    for(ll i = 2; i * i <= R; ++i){
        if(isprime[i]){
            for(ll j = max(2LL,(L - 1 + i) / i) * i; j <= R; j += i){
                isprime_big[j - L] = 0;
            }
        }
    }
}