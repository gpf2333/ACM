#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    long long l = 1, r, mid, n, a;
    cin >> n;
    r = n;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (mid * (mid + 1) / 2 < n)
            l = mid + 1;
        else
            r = mid;
    }
    a = n - l * (l - 1) / 2;
    if (l % 2 == 0)
        cout << a << '/' << l + 1 - a;
    else
        cout << l + 1 - a << '/' << a;
    return 0;
}