
def exgcd(a, b):
    if b == 0:
        return (a, 1, 0)
    else :
        (d, y, x) = exgcd(b, a % b)
        y -= x * (a // b)
        return (d, x, y)

def excrt(r, m, n):
    mo = m[0]
    re = r[0]
    for i in range(1, n):
        (d, x, y) = exgcd(mo, m[i])
        if ((r[i] - re) % d) != 0:
            return (0, re, mo) 
        x = (r[i] - re) // d * x % (m[i] // d)
        re += x * mo
        mo = (mo // d) * m[i]
        re = re % mo
    re = (re + mo) % mo
    return (1, re, mo)

n, m = map(int, input().split())
a = []
b = []
for i in range(0, n):
    x, y = map(int, input().split())
    a.append(x)
    b.append(y)

(ok, re, mo) = excrt(b, a, n)

if ok == 0:
    print("he was definitely lying")
else:
    if re > m:
        print("he was probably lying")
    else :
        print(re)
