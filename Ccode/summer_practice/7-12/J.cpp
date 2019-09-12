#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+100;
int a[maxn],b[maxn];
int s[maxn],e[maxn];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d", &a[i], &b[i]);
        }
        sort(a, a + n);
        sort(b, b + n);
        int i = 1, j = 0;
        int in = 1;
        int mx = 1;
        int cnt = 1;
        s[1] = a[0];
        while (i < n && j < n)
        {
            if (a[i] < b[j])
            {
                in++;
                if (in > mx)
                {
                    s[++cnt] = a[i];
                    mx = in;
                }
                i++;
            }
            else
            {
                in--;
                j++;
            }
        }
        i = n-2;
        j = n-1;
        int ans = mx;
        in = 1;
        mx = 1;
        int cntt = 1;
        e[1] = b[n-1];
        while (i >= 0 && j >= 0)
        {
            if (a[j] < b[i])
            {
                in++;
                if (in > mx)
                {
                    e[++cntt] = b[i];
                    mx = in;
                }
                i--;
            }
            else
            {
                in--;
                j--;
            }
        }
        ll sum = 0;
        for(int k = 1;k<=cntt;k++)
        {
            sum += (e[k]-s[k]);
        }
        printf("%d %lld\n", mx, sum);
    }
}