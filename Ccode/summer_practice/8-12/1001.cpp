#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (int)a; i <= (int)b; i++)
#define ll long long
using namespace std;
const int maxn = 100009;
int flag, ctc, len[4], x, y, z;
char S[3][maxn];
char a[maxn], c[maxn];
int deal(int idc, int ida, int st)
{
    if (flag)
        return 0;
    int add = len[idc] - len[ida] - st + 1;
    rep(i, 1, add) a[i] = '0';
    for (int i = len[ida], j = add; i >= 1; i--)
        a[++j] = S[ida][i];
    int la = len[ida] + add, lc = len[idc];
    for (int i = len[idc], j = 0; i >= 1; i--)
    {
        c[++j] = S[idc][i];
    }
    if (la > lc)
        return 0;
    if (la == lc)
    {
        for (int i = la; i >= 1; i--)
        {
            if (a[i] == c[i])
                continue;
            if (a[i] > c[i])
                return 0;
            break;
        }
    }
    int bit = 0;
    rep(i, 1, la)
    {
        c[i] -= bit;
        if (c[i] < a[i])
        {
            c[i] += 10;
            bit = 1;
        }
        else
            bit = 0;
        a[i] = c[i] - a[i] + '0';
    }
    int i = 0;
    for (i = la; i >= 1 && a[i] == '0'; i--)
        ;
    if (i >= 1)
    {
        len[3] = i;
        for (int d = 1, u = i; d <= u; d++, u--)
        {
            swap(a[d], a[u]);
        }
        return add;
    }
    return 0;
}
int ck(int idb)
{
    int post = len[3], posb = len[idb];
    while (a[post] == '0')
        post--;
    while (S[idb][posb] == '0')
        posb--;
    while (post >= 1 && posb >= 1)
    {
        if (a[post] == S[idb][posb])
        {
            post--, posb--;
            continue;
        }
        break;
    }
    return post == 0 && posb == 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s%s%s", S[0] + 1, S[1] + 1, S[2] + 1);
        len[0] = strlen(S[0] + 1), len[1] = strlen(S[1] + 1), len[2] = strlen(S[2] + 1);
        ctc = max(0, max(len[0], len[1]) + 3 - len[2]);
        for (int i = len[2] + 1; i <= len[2] + ctc; i++)
        {
            S[2][i] = '0';
        }
        len[2] += ctc;
        z = ctc;
        flag = 0;
        int l1, l2;
        if (S[2][1] == '1' && (l1 = deal(2, 0, 2)))
        {
            if (ck(1))
            {
                x = l1, y = len[3] - len[1], flag = 1;
            }
        }
        if (l1 = deal(2, 0, 1))
        {
            if (ck(1))
            {
                x = l1, y = len[3] - len[1], flag = 1;
            }
        }

        if (S[2][1] == '1' && (l1 = deal(2, 1, 2)))
        {
            if (ck(0))
            {
                y = l1, x = len[3] - len[0], flag = 1;
            }
        }
        if (l1 = deal(2, 1, 1))
        {
            if (ck(0))
            {
                y = l1, x = len[3] - len[0], flag = 1;
            }
        }
        if (flag)
            printf("%d %d %d\n", x, y, z);
        else
            printf("-1\n");
    }
    return 0;
}

/*
40
23 39 62
40500 643 1048
23 39 62
2 31 51
1 1 1
20 49 5010000
20 49 5100000
2000000 490000000000000000000 51
200 490000000 51
2000000 49000 51
40500 643 1048
6003000000 101003 61040030000
19954009 800760010 10003001
5 6 11
1000000000000000000000 2 3
11111111 11 11111121000
9913293911030092 325365190001 9945830430030192000
99132939110300920000000000 3253651900010000000000 9945830430030192000
3 5 53
102 9080 1010000
*/
