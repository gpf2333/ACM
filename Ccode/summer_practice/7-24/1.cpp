#include "bits/stdc++.h"
 
using namespace std;
const double eps = 1e-8;
#define reg register
#define lowbit(x) x&-x
#define pll pair<ll,ll>
#define pii pair<int,int>
#define fi first
#define se second
#define makp make_pair
 
int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    return (x > 0) ? 1 : -1;
}
 
typedef long long ll;
typedef unsigned long long ull;
const ull hash1 = 201326611;
const ull hash2 = 50331653;
const int N = 300000 + 10;
const int M = 1000 + 10;
const int inf = 0x3f3f3f3f;
const ll mod = 998244353;
ll ret[N];
ull ha[N], pp[N];
 
ull getha(int l, int r) {
    if (l == 0) return ha[r];
    return ha[r] - ha[l - 1] * pp[r - l + 1];
}
 
bool check(int l, int r) {
    int len = r - l + 1;
    int mid = (l + r) >> 1;
    if (len & 1) return getha(l, mid) == getha(mid, r);
    else return getha(l, mid) == getha(mid + 1, r);
}
 
 
struct Palindromic_Tree {
    int nxt[N][30], fail[N], cnt[N];
    int num[N], len[N], s[N], id[N];
    int last, n, p;
 
    int newnode(int l) {
        memset(nxt[p], 0, sizeof(nxt[p]));
        cnt[p] = num[p] = 0;
        len[p] = l;
        return p++;
    }
 
    void init() {
        p = 0;
        newnode(0), newnode(-1);
        last = n = 0;
        s[0] = -1;
        fail[0] = 1;
    }
 
    int get_fail(int x) {
        while (s[n - len[x] - 1] != s[n]) x = fail[x];
        return x;
    }
 
    void add(int c) {
        c -= 'a';
        s[++n] = c;
        int cur = get_fail(last);
        if (!nxt[cur][c]) {
            int now = newnode(len[cur] + 2);
            fail[now] = nxt[get_fail(fail[cur])][c];
            nxt[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = nxt[cur][c];
        cnt[last]++, id[last] = n;
    }
 
    ll Count() {
        for (int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
        for (int i = 2; i < p; i++) {
            cout << id[i] << " " << id[i] - len[i] << " " << id[i] - 1 << endl;
            if (check(id[i] - len[i], id[i] - 1)) {
                ret[len[i]] += cnt[i];
            }
        }
        return 0;
    }
} pam;
 
char str[N];
 
int main() {
    pp[0] = 1;
    for (int i = 1; i < N; i++) {
        pp[i] = hash1 * pp[i - 1];
    }
    while (~scanf("%s", str)) {
        memset(ret, 0, sizeof(ret));
        pam.init();
        int len = strlen(str);
        ha[0] = str[0];
        for (int i = 0; i < len; i++) {
            pam.add(str[i]);
        }
        for (int i = 1; i < len; i++) {
            ha[i] = ha[i - 1] * hash1 + str[i];
        }
        pam.Count();
        printf("%lld", ret[1]);
        for (int i = 2; i <= len; i++) {
            printf(" %lld", ret[i]);
        }
        printf("\n");
    }
    return 0;
}
