#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define LC(x) (x<<1)
#define RC(x) ((x<<1)+1)
#define MID(x,y) ((x+y)>>1)
#define fin(name) freopen(name,"r",stdin)
#define fout(name) freopen(name,"w",stdout)
#define CLR(arr,val) memset(arr,val,sizeof(arr))
#define FAST_IO ios::sync_with_stdio(false);cin.tie(0);
typedef pair<int, int> pii;
typedef long long LL;
const double PI = acos(-1.0);
const int N = 130;
namespace ac {
    struct Trie
    {
        int nxt[2], fail, st[2];
        void init()
        {
            nxt[0] = nxt[1] = -1;
            st[0] = st[1] = fail = 0;
        }
    } L[N * 3];
    int sz;
    void init()
    {
        sz = 0;
        L[sz++].init();
    }
    inline int newnode()
    {
        L[sz].init();
        return sz++;
    }
    void ins(char s[], int len, int id, int index)
    {
        int u = 0;
        for (int i = 0; i < len; ++i)
        {
            int v = s[i] - '0';
            if (L[u].nxt[v] == -1)
                L[u].nxt[v] = newnode();
            u = L[u].nxt[v];
        }
        L[u].st[index] |= (1 << id);
    }
    void build()
    {
        L[0].fail = 0;
        queue<int>Q;
        for (int i = 0; i < 2; ++i)
        {
            int &v = L[0].nxt[i];
            if (~v)
            {
                Q.push(v);
                L[v].fail = 0;
            }
            else
                v = 0;
        }
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            int uf = L[u].fail;
            L[u].st[0] |= L[uf].st[0];
            L[u].st[1] |= L[uf].st[1];
            for (int i = 0; i < 2; ++i)
            {
                int &v = L[u].nxt[i];
                if (~v)
                {
                    Q.push(v);
                    L[v].fail = L[uf].nxt[i];
                }
                else
                    v = L[uf].nxt[i];
            }
        }
    }
}
char s[N], rs[N];
int dp[2][N * 3][1 << 6];
const int mod = 998244353;

int main(void)
{
    int TC, n, L, i, j, k;
    scanf("%d", &TC);
    while (TC--)
    {
        ac::init();
        CLR(dp, 0);
        scanf("%d%d", &n, &L);
        for (i = 0; i < n; ++i)
        {
            scanf("%s", s);
            int len = strlen(s);
            ac::ins(s, len, i, 0);//左半边
            for (j = 0; j < len; ++j)
                rs[j] = s[len - 1 - j] == '1' ? '0' : '1';
            ac::ins(rs, len, i, 0);//右半边等价映射到左半边
            for (j = 0; j < len - 1; ++j) //把超出中线的右半部分也等价映射到左半边
            {
                int lenl = j + 1, lenr = len - lenl;
                int canmap = 1;
                for (k = 0; k < min(lenl, lenr); ++k)
                {
                    if (s[j - k] == s[j + 1 + k])
                    {
                        canmap = 0;
                        break;
                    }
                }
                if (canmap)
                {
                    string str = string(s, 0, lenl);
                    for (k = 2 * lenl; k < len; ++k)
                        str = (s[k] == '1' ? '0' : '1') + str;
                    strcpy(rs, str.c_str());
                    ac::ins(rs, str.size(), i, 1);
                }
            }
        }
        ac::build();
        int now = 0, nxt = 1;
        int R = 1 << n;
        dp[0][0][0] = 1;
        for (i = 0; i < L; ++i)
        {
            CLR(dp[nxt], 0);
            for (j = 0; j < ac::sz; ++j)
            {
                for (k = 0; k < R; ++k)
                {
                    if (dp[now][j][k])
                    {
                        for (int s = 0; s < 2; ++s)
                        {
                            int v = ac::L[j].nxt[s];
                            int vst = k | ac::L[v].st[0];
                            if (i == L - 1)
                                vst |= ac::L[v].st[1];
                            dp[nxt][v][vst] = (dp[nxt][v][vst] + dp[now][j][k]) % mod;
                        }
                    }
                }
            }
            swap(now, nxt);
        }
        int ans = 0;
        for (i = 0; i < ac::sz; ++i)
            ans = (ans + dp[now][i][R - 1]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}