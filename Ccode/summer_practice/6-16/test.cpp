// #include <bits/stdc++.h>
// using namespace std;
// const int maxn = 1015;
// char s[maxn][maxn];
// bool vis[maxn][maxn];
// vector<int>a;
// int h, n, m;
// int dir1[6][2] = {-1, 0, -1, 1, 0, -1, 0, 1, 1, 0, 1, 1};
// int dir2[6][2] = {1, -1, 1, 0, 0, 1, 0, -1, -1, -1, -1, 0};
// int c = 0;
// void dfs(int x, int y)
// {
//     vis[x][y] = true;
//     ++c;
//     if (x % 2 == 1)
//     {
//         for (int i = 0; i < 6; ++i)
//         {
//             int nx = x + dir1[i][0];
//             int ny = y + dir1[i][1];
//             if (nx < 0 || nx >= n || ny < 0 || ny >= m)
//             {
//                 continue;
//             }
//             if ((s[nx][ny] == '#') || vis[nx][ny])
//                 continue;
//             dfs(nx, ny);
//         }
//     }
//     else
//     {
//         for (int i = 0; i < 6; ++i)
//         {
//             int nx = x + dir2[i][0];
//             int ny = y + dir2[i][1];
//             if (nx < 0 || nx >= n || ny < 0 || ny >= m)
//                 continue;
//             if (s[nx][ny] == '#' || vis[nx][ny])
//                 continue;
//             dfs(nx, ny);
//         }
//     }
//     return;
// }

// bool cmp(const int a, const int b){
//     return a > b;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin >> h >> n >> m;
//     for (int i = 0; i < n; ++i)
//     {
//         for(int j = 0; j < m; ++j)
//         {
//             cin >> s[i][j];
//         }
//     }
//     memset(vis, 0, sizeof(vis));
//     for (int i = 0; i < n; ++i)
//     {
//         for (int j = 0; j < m; ++j)
//         {
//             if ((s[i][j] == '.') && vis[i][j] == false)
//             {
//                 c = 0;
//                 dfs(i, j);
//                 a.push_back(c);
//             }
//         }
//     }
//     sort(a.begin(), a.end(), cmp);
//     int sum = 0;
//     int ans = 0;
//     for(auto it = a.begin(); it != a.end(); ++it){
//         sum += (*it);
//         ++ans;
//         if(sum >= h) break ;
//     }
//     cout << ans << endl;
//     return 0;
// }

#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i = (a); i != (b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()

template<class T> using min_queue = priority_queue<T, vector<T>, greater<T> >;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int maxn = 5e5;

int N, M, X[maxn], L[maxn];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	REP(i, N) cin >> X[i];
	REP(i, M) cin >> L[i];

	for (int i = N - 1; i > 0; i--) X[i] -= X[i - 1];
	X[0] = 0;

	sort(L, L + M);

	// match greedily
	min_queue<ii> q;
	for (int i = 1; i < N; i++) q.emplace(X[i], i + 1);

	int ptr = 0;
	while (!q.empty() && ptr < M) {
		ii cur = q.top(); q.pop();
        cout << cur.x << " " << cur.y << endl;
		if (cur.y < N) {
			// add the next one.
			q.emplace(cur.x + X[cur.y], cur.y + 1);
		}

		if (L[ptr] >= cur.x) {
			// we got a match!
			ptr++;
		} else break;
	}

	if (ptr == M) cout << "yes" << endl;
	else cout << "no" << endl;

	return 0;
}