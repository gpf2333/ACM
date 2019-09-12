#include <bits/stdc++.h>
using namespace std;
const int maxn = 150;
int dis[maxn][maxn];
const int inf = 1e5;
const int mx = 1e6 + 10;
int keypath[mx];
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; s[j]; j++){
            if(s[j] == '1') dis[i][j] = 1;
            else dis[i][j] = inf;
        }
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dis[i][j] > dis[i][k] + dis[k][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    for (int i = 0; i < n; i++) dis[i][i] = inf;
    int m;
    cin >> m;
    vector<int> ans;
    for(int i = 1; i <= m; i++){
        cin >> keypath[i];
        --keypath[i];
    }
    ans.push_back(keypath[1]);
    for(int i = 1, j; i < m; i = i + j - 1){
        for(j = 1; j + i  <= m; j++){
            if(dis[keypath[i]][keypath[i + j]] != j) break;
        }
        ans.push_back(keypath[i + j - 1]);
    }
    cout << ans.size() << endl;
    for(auto it:ans){
        cout << it + 1 << " ";
    }
    cout << endl;

}