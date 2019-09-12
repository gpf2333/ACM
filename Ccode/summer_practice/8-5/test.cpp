#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e4 + 325;
vector<string> vec;
vector<int> ans;
//int p[maxn];
ll fac[25];
void init(){
    fac[0] = 1;
    for(int i = 1; i <= 10; i++)
    {
        fac[i] = fac[i - 1] * i;
    }
}
int last;
bool cmp(string v1, string v2){
    if(v1[0] - '0' - last != v2[0] - '0' - last && last != -1) return v1[0] - '0' - last < v2[1] - '0' - last;
    for(int i = 1; i < v1.size(); i++){
        if(v1[i] - v1[i - 1] != v2[i] - v2[i - 1]) return v1[i] - v1[i - 1] < v2[i] - v2[i - 1];
    }
    //return false;
}

int main(){
    int t;
    init();
    scanf("%d", &t);
    while(t--){
        int n, k;
        scanf("%d%d", &n, &k);
        ans.clear();
        int pos = 0;
        int a[10];
        vec.clear();
        for(int i = 1; i <= 8; i++)
        {
            if(fac[i] > k){
                pos = i;
                break;
            }
        }
        if(n <= 8){
            for(int i = 1; i <= n; i++){
                a[i] = i;
            }
            last = - 1;
            do{
                string tmp;
                for(int i = 1; i <= n; i++){
                    tmp += (a[i] + '0');
                }
                vec.push_back(tmp);
            }while(next_permutation(a + 1, a + 1 + n));
            sort(vec.begin() , vec.end(), cmp);
            for(int i = 0; i < vec[k - 1].size(); i++){
                ans.push_back((int)(vec[k - 1][i] - '0'));
            }
        }
        else if(n >= 9){
            ans.push_back(n);
            for(int i = 1; i <= n - 1 - pos; i++){
                ans.push_back(i);
            }
            for(int i = n - pos; i <= n - 1; i++){
                a[i - n + pos + 1] = i;
            }
            int minn = n - pos;
            last = n - 1 - pos;
            // cout << last << endl;
            do{
                string tmp;
                for(int i = 1; i <= pos; i++){
                    tmp += (a[i] - minn - '0');
                }
                vec.push_back(tmp);
            }while(next_permutation(a + 1, a + 1 + pos));
            sort(vec.begin(), vec.end(), cmp);
            for(int i = 0; i < vec[k - 1].size(); i++){
                ans.push_back((int)(vec[k - 1][i] + '0'));
            }
        }
        for(int j = 0; j < ans.size(); j++){
            printf("%d ", ans[j]);
        }
        printf("\n");
    }
}