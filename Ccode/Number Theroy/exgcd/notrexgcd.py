
def exgcd(m, n):
    if n == 0:
        return (m, 1, 0)
    else:
        a1 = b = 1
        a = b1 = 0
        c = m
        d = n
        q = c // d 
        r = c % d    
        while r > 0:
            c = d
            d = r
            t = a1
            a1 = a
            a = t - q * a
            t = b1
            b1 = b
            b = t - q * b

            q = c // d
            r = c % d
        x = a
        y = b
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
