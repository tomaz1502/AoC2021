a = []

while True:
    try:
        line = input()
    except:
        break
    n = int(line)
    a += [n]

s = 0
for i in range(3):
    s += a[i]

last = s
cnt = 0
for i in range(1, len(a) - 2):
    s -= a[i - 1]
    s += a[i + 2]
    if s > last:
        cnt += 1
    last = s

print(cnt)
