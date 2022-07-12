from cs50 import get_float


def get_rest(n, coin_value):
    cnt = n//coin_value
    rest = n % coin_value
    return rest, cnt


while True:
    n = get_float("Change owed: ")
    if n > 0:
        break

n = int(100*n)

cnt = 0
n, cnt_0 = get_rest(n, 25)
cnt += cnt_0

n, cnt_0 = get_rest(n, 10)
cnt += cnt_0

n, cnt_0 = get_rest(n, 5)
cnt += cnt_0

n, cnt_0 = get_rest(n, 1)
cnt += cnt_0

print(cnt)
