#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 50;
char s[maxn], ans[maxn];
int main()
{
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%s", s);
        int i = 0, j = strlen(s) - 1;
        while (s[i++] == '9'){
            if (i == j + 1){
                for (s[0] = '1', j++; i > 0; i--){
                    s[i] = '0';
                }
            }
        }
        for (i = 0; i <= j - i; i++)
            ans[i] = ans[j - i] = s[i];
        if (strcmp(ans, s) <= 0)
        {
            while (ans[--i] == '9') ;
            ans[i] = ans[j - i] = ++ans[i];
            for(i++; i <= j - i; i++)
                ans[i] = ans[j - i] = '0';
        }
        puts(ans);
    }
    return 0;
}