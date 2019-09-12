#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdio>

using namespace std;

#define MAXN 55

struct Node
{
    int l, t, r, b;
    int x1, x2, y1, y2;
}node[MAXN];

int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
int tempx[2 * MAXN], tempy[2 * MAXN];
bool vis[2 * MAXN][2 * MAXN];
bool visx[2 * MAXN][2 * MAXN], visy[2 * MAXN][2 * MAXN];
int tx, ty, n;

bool check(int x, int y, int xt, int yt)
{
    bool flag = true;

    if (x == xt)
    {
        int yc = max(y, yt);

        for (int i = 0; i < n; i++)
        {
            if (yc == node[i].y1 || yc == node[i].y2)
            {
                if (node[i].x1 <= x && x + 1 <= node[i].x2)
                {
                    flag = false;
                    break;
                }
            }
        }
    }
    else
    {
        int xc = max(x, xt);

        for (int i = 0; i < n; i++)
        {
            if (xc == node[i].x1 || xc == node[i].x2)
            {
                if (node[i].y1 <= y && y + 1 <= node[i].y2)
                {
                    flag = false;
                    break;
                }
            }
        }
    }

    return flag;
}

bool check2(int x, int y, int d)
{
    if (d == 0)
    {
        return !visy[x + 1][y];
    }
    else if (d == 2)
    {
        return !visy[x][y];
    }
    else if (d == 3)
    {
        return !visx[x][y];
    }
    else
    {
        return !visx[x][y + 1];
    }
}

void dfs(int x, int y)
{
    vis[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        int xt = x + dir[i][0], yt = y + dir[i][1];

        if (xt >= 0 && xt <= tx && yt >= 0 && yt <= ty)
        {
            if (check2(x, y, i) && !vis[xt][yt])
            {
                dfs(xt, yt);
            }
        }
    }
}

void input()
{


        tx = ty = 0;
        n = 2;
        for (int i = 0; i < n; i++)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            node[i].l = x1;
            node[i].t = y2;
            node[i].r = x2;
            node[i].b = y1;
            tempx[tx++] = node[i].l;
            tempx[tx++] = node[i].r;
            tempy[ty++] = node[i].t;
            tempy[ty++] = node[i].b;
        }

        sort(tempx, tempx + tx);
        sort(tempy, tempy + ty);

        tx = unique(tempx, tempx + tx) - tempx;
        ty = unique(tempy, tempy + ty) - tempy;

        int x1, y1, x2, y2;
        memset(visx, false, sizeof(visx));
        memset(visy, false, sizeof(visy));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < tx; j++)
            {
                if (node[i].l == tempx[j])
                {
                    x1 = j + 1;
                }
                if (node[i].r == tempx[j])
                {
                    x2 = j + 1;
                }
            }

            for (int j = 0; j < ty; j++)
            {
                if (node[i].t == tempy[j])
                {
                    y2 = j + 1;
                }
                if (node[i].b == tempy[j])
                {
                    y1 = j + 1;
                }
            }

            node[i].x1 = x1, node[i].x2 = x2, node[i].y1 = y1, node[i].y2 = y2;
            for (int j = x1; j <= x2 - 1; j++)
            {
                visx[j][y1] = visx[j][y2] = true;
            }

            for (int j = y1; j <= y2 - 1; j++)
            {
                visy[x1][j] = visy[x2][j] = true;
            }
        }

        memset(vis, false, sizeof(vis));

        int ans = 0;

        for (int i = 0; i <= tx; i++)
        {
            for (int j = 0; j <= ty; j++)
            {
                if (!vis[i][j])
                {
                    dfs(i, j);
                    ans++;
                }
            }
        }
        printf("%d\n", ans);

}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        input();
    }
    return 0;
}