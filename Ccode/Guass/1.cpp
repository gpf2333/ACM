#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e4 + 1000;
const int maxm = 2e5 + 1000; 
struct Edge{
	int v, next;
	ll w;
} edge[maxm];
int n, m;
int head[maxn], tot;
int vis[maxn];
int cnt;
ll val[maxm];
ll dis[maxn];

void init(int n){
	tot = cnt = 0;
	for(int i = 0; i <= n; ++i){
		head[i] = vis[i] = -1;
	}
} 

inline void addedge(int u, int v, ll w){
	edge[tot].v = v;
	edge[tot].w = w;
	edge[tot].next = head[u];
	head[u] = tot++;
}
 
void dfs (int u, int fa, int pre){
	vis[u] = pre;
	for(int i = head[u]; ~i; i = edge[i].next){
		int v = edge[i].v;
		if(v == fa) continue;
		if(vis[v] != -1){
			if(vis[v] <= pre)
				val[cnt++] = dis[u] ^ dis[v] ^ edge[i].w;
		}
		else{
			dis[v] = dis[u] ^ edge[i].w;
			dfs(v, u, pre + 1);
		}
	}
}
 
ll xorguass(int n){
	int row = 0;
	for(int i = 61; i >= 0; --i){
		int j;
		for(j = row; j < n; ++j){
			if(val[j] & (1LL << i)) break;
		}
		if(j < cnt){
			std::swap(val[row], val[j]);
			for(j = 0; j < n; ++j){
				if(j == row) continue ;
				if(val[j] & (1LL << i)) val[j] ^= val[row];
			}
			++row;
		}
	}
	ll ans = 0;
	for(int i = 0; i < row; ++i){
		// ans = max(ans, ans ^ val[i]);
		ans = ans ^ val[i];
	}
	return ans;
}
 
int main(){
	int T, kase = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		init(n);
		int u, v;
		ll w;
		for(int i = 0; i < m; ++i){
			scanf("%d%d%lld", &u, &v, &w);
			addedge(u, v, w);
			addedge(v, u, w);
		}
		dis[0] = dis[1] = 0;
		dfs(1,-1, 0);
		printf("Case #%d: %lld\n", ++kase,xorguass(cnt));
	}
	return 0;
}