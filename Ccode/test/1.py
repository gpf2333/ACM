# n = input()
# a = map(int, input().split())
# a = sorted(a)
# v = a[0]
# ok = True
# for i in a:
#     if i % v > 0:
#         ok = False
#         break

# if ok:
#     print(v)
# else:
#     print(-1)

import sys
from functools import cmp_to_key
def cmp(x, y):
    if (x + y) > (y + x):
        return 1
    elif (x + y) < (y + x):
        return -1
    else:
        return 0

s = input().split()
s.sort(key = cmp_to_key(cmp), reverse = True)
ans = "".join(s).strip('0')
print(ans)
