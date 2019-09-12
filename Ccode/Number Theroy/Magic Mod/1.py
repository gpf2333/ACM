# def Min(a, b):
#     if a > b:
#         return b
#     else:
#         return a

# def calc(x, p):
#     res = 0
#     while x > 0:
#         res = res + x // p
#         x = x // p
#     return res


# prime = [2, 3, 5, 7, 11]
# a, b = map(int, input().split())
# ans = 1
# for v in prime:
#     ans = ans * (v ** Min(calc(a, v), calc(b, v)))

# print(ans) 

# s = input()
# print(max(map(int, (s, s[:-1], s[:-2] + s[-1]))))



n = 210
res = 0
cnt = 2
while cnt <= 20:
    res = res + n
    s = str(res)
    if len(s) > cnt:
        print(cnt + 1, res)
        cnt = cnt + 1
        

