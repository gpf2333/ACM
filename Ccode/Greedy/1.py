p = int(input())
s = str(2**p - 1)
l = len(s)
print(l)

if (l < 500):
    t = 500 - l
    ss = ""
    for i in range(0, t):
        ss = ss + "0"
    ss += s
    print(ss)
else:
    ss = s[l - 500 : l]
    print(ss)
    print(len(ss))
