#include <bits/stdc++.h>
using namespace std;

#define LL long long
const int N = 500010;

char s[N];
int n, m = 255, sa[N], tp[N];
int rk[N], _rk[N], bin[N], height[N];

void base_sort () {
    for (int i = 0; i <= m; ++i) bin[i] = 0;
    for (int i = 1; i <= n; ++i) bin[rk[tp[i]]]++;
    for (int i = 1; i <= m; ++i) bin[i] += bin[i - 1];
    for (int i = n; i >= 1; --i) sa[bin[rk[tp[i]]]--] = tp[i];
}

void suffix_sort () {
    for (int i = 1; i <= n; ++i) {
        tp[i] = i;
        rk[i] = s[i - 1];
    }
    base_sort ();
    for (int w = 1; w <= n; w <<= 1) {
        int cnt = 0;
        for (int i = n - w + 1; i <= n; ++i) {
            tp[++cnt] = i;
        }
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > w) {
                tp[++cnt] = sa[i] - w;
            }
        }
        base_sort ();
        memcpy (_rk, rk, sizeof (rk));
        rk[sa[1]] = cnt = 1;
        for (int i = 2; i <= n; ++i) {
            rk[sa[i]] = _rk[sa[i]] == _rk[sa[i - 1]] && _rk[sa[i] + w] == _rk[sa[i - 1] + w] ? cnt : ++cnt;
        }
        if (cnt == n) break;
        m = cnt;
    }
    // printf ("sa : ");for (int i = 1; i <= n; ++i) printf ("%d ", sa[i]); printf ("\n");
}

void get_height () {
    int  k = 0;
    for (int i = 1; i <= n; ++i) {
        if (k) k--;
        int j = sa[rk[i] - 1];
        while (s[i + k - 1] == s[j + k - 1]) ++k;
        height[rk[i]] = k; 
    }
    // printf ("height : ");
    // for (int i = 1; i <= n; ++i) {
    //  printf ("%d ", height[i]);
    // }
    // printf ("\n");
}

struct node {
    int pos, val;
    node (int ppos = 0, int vval = 0) {pos = ppos, val = vval;}
};

node sta[N]; int top;
LL f[N];

int main () {
    scanf ("%s", s);
    n = strlen (s);
    suffix_sort ();
    get_height ();
    // for(int i = 1; i <= n; ++i){
    //     cout << sa[i] << " ";
    // }
    // cout << endl;
    for (int i = 1; i <= n; ++i) {
        while (top > 0 && sta[top].val > height[i]) --top;
        //使sta[top].val <= height[i];
        if (top > 0) {
            int p = sta[top].pos; //p记录控制范围
            f[i] = f[p] + (i - p) * height[i];
        } else {
            f[i] = i * height[i];
        }
        sta[++top] = node (i, height[i]);
        ///cout << height[i] << " ";
    }
    // puts("");
    LL ans = 1LL * (n - 1) * n * (n + 1) / 2;
    for (int i = 1; i <= n; ++i) {
        ans -= 2 * f[i];
    }
    cout << ans << endl;
} 