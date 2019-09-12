#include <bits/stdc++.h>
using namespace std;
int n, x, k;
map<int, int> mp;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        ++mp[x];
    }
    int sum = 0;
    bool flag = 0;
    for (auto it: mp){
        if(it.second & 1){
            if(flag){
                flag = 0;
                sum += (it.second - 1);
            }else{
                flag = 1;
                sum += it.second;
            }
        }else{
            sum += it.second;
        }
    }
    printf("%d\n", sum);
    return 0;
}