#include<bits/stdc++.h>
#define inv inline void
#define ini inline int
#define maxn 100050
using namespace std;
int st[20][maxn];
int ndtot, N;
struct segtree { int l, r, size; segtree *ch[2]; }pool[maxn * 30], *root[maxn];
void ins(segtree *pre, segtree *now, int pos)
{
    int mid = (pre->l + pre->r) >> 1;
    *now = *pre; now->size++;
    if (pre->l == pre->r)return;
    if (pos <= mid)ins(pre->ch[0], now->ch[0] = pool + ++ndtot, pos);
    if (pos > mid)ins(pre->ch[1], now->ch[1] = pool + ++ndtot, pos);
}
int find(segtree *pre, segtree *now, int k)
{
    int sz;
    if (pre->l == pre->r)return pre->l;
    sz = now->ch[0]->size - pre->ch[0]->size;
    if (k <= sz)return find(pre->ch[0], now->ch[0], k);
    return find(pre->ch[1], now->ch[1], k - sz);
}
void build(segtree *p, int l, int r)
{
    int mid = (l + r) >> 1;
    p->l = l, p->r = r, p->size = 0;
    if (l == r)return;
    build(p->ch[0] = pool + ++ndtot, l, mid);
    build(p->ch[1] = pool + ++ndtot, mid + 1, r);
}
 
 
char s[maxn];
int y[maxn], x[maxn], c[maxn], sa[maxn], rk[maxn], height[maxn];
int n, m;
inv get_SA() {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i) ++c[x[i] = s[i]];
    for (int i = 2; i <= m; ++i) c[i] += c[i - 1];
    for (int i = n; i >= 1; --i) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; ++i) y[++num] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; ++i) c[i] = 0;
        for (int i = 1; i <= n; ++i) ++c[x[i]];
        for (int i = 2; i <= m; ++i) c[i] += c[i - 1]; 
        for (int i = n; i >= 1; --i) sa[c[x[y[i]]]--] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1;
        num = 1;
        for (int i = 2; i <= n; ++i)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
        if (num == n) break;
        m = num;
    }
}
inv get_height() {
    int k = 0;
    for (int i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (int i = 1; i <= n; ++i) {
        if (rk[i] == 1) continue;
        if (k) --k;
        int j = sa[rk[i] - 1];
        while (j + k <= n && i + k <= n && s[i + k] == s[j + k]) ++k;
        height[rk[i]] = k;
    }
}
void build_st() {
    for (int i = 1; i <= n; i++) st[0][i] = height[i];
    for (int k = 1; k <= 19; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << k - 1)]);
        }
    }
}
int lcp(int x, int y) {
    int l = rk[x], r = rk[y];
    if (l > r) swap(l, r);
    if (l == r) return n - sa[l];
    int t = log2(r - l);
    return min(st[t][l + 1], st[t][r - (1 << t) + 1]);
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int len, q;
        scanf("%d%d", &len, &q);
        scanf("%s", s + 1);
        n = strlen(s + 1);
        m = 123;
        get_SA();
        get_height();
        build_st();
        N = n;
        ndtot = 0;
        build(root[0] = pool + ++ndtot, 1, N);
        for (int i = 1; i <= N; i++)ins(root[i - 1], root[i] = pool + ++ndtot, sa[i]);
        // for(int i = 1; i <= N; ++i){
        //     cout << i << " " << sa[i] << " " << height[i] << " " << rk[i] << endl;
        // }
        while (q--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int ll, rr;
            int length = r - l + 1;
            int left = 1, right = rk[l];
            int ans = rk[l];
            while(left<=right){
                int mid = (left + right) / 2;
                if (lcp(sa[mid], l) >= length) {
                    right = mid-1;
                    ans = mid;
                }
                else {
                    left = mid + 1;
                }
            }
            ll = ans;
            ans = rk[l];
            left = rk[l], right = n;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (lcp(sa[mid], l) >= length) {
                    left = mid+1;
                    ans = mid;
                }
                else {
                    right = mid - 1;
                }
            }
            rr = ans;
            // cout << ll << " " << rr << endl; 
            if (rr - ll + 1 < k) printf("-1\n");
            else printf("%d\n", find(root[ll - 1], root[rr], k));
        } 
    }
}