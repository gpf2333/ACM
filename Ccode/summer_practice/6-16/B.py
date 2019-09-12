n = int(input())
s = input()
mid = n // 2
ans = int(s)
for i in range(0, mid, 1):
    a = s[0: mid-i]
    b = s[mid - i: n]
    if int(b[0]) == 0:
        continue
    c = int(a, 10) + int(b, 10)
    ans = c
    break
    
for i in range(1, mid + 1, 1):
    ok = True
    a = s[0: mid+i]
    b = s[mid + i: n]
    if int(b[0]) == 0:
        continue
    c = int(a, 10) + int(b, 10)
    if ans > c:
        ans = c
    break 

print(ans)
