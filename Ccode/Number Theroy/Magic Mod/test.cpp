// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int maxn = 1e6 + 10;
// const int mod = 1e9 + 7;
// bool isprime[maxn];
// int cntp, prime[maxn], phi[maxn];
// void init(){
//     memset(isprime, 1, sizeof(isprime));
//     cntp = isprime[0] = isprime[1] = 0;
//     phi[1] = 1;
//     for(int i = 2; i < maxn; ++i){
//         if(isprime[i]){
//             prime[++cntp] = i;
//             phi[i] = i - 1;
//         }
//         for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
//             isprime[i * prime[j]] = 0;
//             if(i % prime[j] == 0){
//                 phi[i * prime[j]] = phi[i] * prime[j];
//                 break ;
//             }
//             phi[i * prime[j]] = phi[i] * phi[prime[j]];
//         }
//     }
// }

// ll getphi(ll n){
//     if(n < maxn) return phi[n];
//     ll res = n;
//     for(int i = 2; (ll)i * i <= n; ++i){
//         if(n % i == 0){
//             res -= res / i;
//             while(n % i == 0) n /= i;
//         }
//     }
//     if(n > 1) res -= res / n;
//     return res;
// }

// ll calc(ll n, ll k){
//     ll res = getphi(n);
//     if(k == 1) return res % mod;
//     int cnt = 2;
//     while(cnt <= k && res != 1){
//         if(cnt % 2 == 1){
//             res = getphi(res);
//         }
//         ++cnt;
//     }
//     return res % mod;
// }

// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0), cout.tie(0);
//     init();
//     ll n, k;
//     cin >> n >> k;
//     cout << calc(n, k) << endl;
//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0), cout.tie(0);
//     int n;
//     int cnt1 = 0, cnt2 = 0;
//     cin >> n;
//     for(int i = 1; i <= n; ++i){
//         int x;
//         cin >> x;
//         if(x == 1) ++cnt1;
//         else ++cnt2;
//     }
//     if(cnt2--) cout << "2 ";
//     if(cnt1--) cout << "1 ";
//     while(cnt2-- > 0) cout << "2 ";
//     while(cnt1-- > 0) cout << "1 ";
//     cout << endl;
//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// const int maxn = 1e7 + 5;
// ll dfs(int n){
//     if(n < 10) return max(1, n);
//     else{
//         return max((n % 10) * dfs(n / 10), 9 * dfs(n / 10 - 1));
//     }
// }
// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0), cout.tie(0);
//     int n;
//     cin >> n;
//     cout << dfs(n) << endl;
// }

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int a[maxn];
struct Node{
    int id, val;
}b[maxn];
inline bool cmp(const Node &a, const Node &b){
    return a.val > b.val;
}
int ans[maxn];
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; ++i){
        scanf("%d", &b[i].val);
        b[i].id = i;
    }
    sort(b + 1, b + n + 1, cmp);
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; ++i){
        ans[b[i].id] = a[i];
    }
    printf("%d", ans[1]);
    for(int i = 2; i <= n; ++i){
        printf(" %d", ans[i]);
    }
    printf("\n");
    return 0;
}