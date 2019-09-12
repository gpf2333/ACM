#include <bits/stdc++.h>
using namespace std;
const int maxn = 1014;
int dir1[6][2] = {-1, 0, -1, 1, 0, -1, 0, 1, 1, 0, 1, 1};
int dir2[6][2] = {1, -1, 1, 0, 0, 1, 0, -1, -1, -1, -1, 0};
char s[maxn][maxn];
int h,n,m;
int c = 0;
bool vis[maxn][maxn];
//vector<int>a;
void dfs(int x, int y)
{
    vis[x][y] = 1;
    c++;
    for(int i = 0; i < 6; ++i)
    {
        int nx = x + ((x % 2 == 1) ? dir1[i][0] : dir2[i][0]);
        int ny = y + ((x % 2 == 1) ? dir1[i][1] : dir2[i][1]);
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(vis[nx][ny] || (s[nx][ny] == '#')) continue;
        vis[nx][ny] = 1;
        dfs(nx,ny);
    }
}

bool cmp(const int a, const int b){
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    priority_queue<int, vector<int>, less<int> > que;
    cin >> h >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
            cin >> s[i][j];
    }
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(s[i][j]=='.' && !vis[i][j])
            {
                c = 0;
                dfs(i,j);
                //a.push_back(c);
                que.push(c);
            }
        }
    }
    //sort(a.begin(), a.end(), cmp);
    int sum =0, ans = 0;
//    for(auto it = a.begin(); it != a.end(); ++it){
//        sum += (*it);
//        ++ans;
//        if(sum >= h) break ;
//    }
    while(!que.empty() && sum < h){
        int top = que.top();
        que.pop();
        sum += top;
        ++ans;
    }
    cout << ans << endl;
    return 0;
}
