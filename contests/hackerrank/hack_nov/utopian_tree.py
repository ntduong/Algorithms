""" Utopian Tree
    Constrains: 1 <= T <= 10 and 0 <= N <= 60. 
"""
def go(x, n):
    i = 1
    while i <= n:
        if i % 2 == 1:
            x *= 2
        else: 
            x += 1
        i += 1
    return x

if __name__ == "__main__":
    T = int(raw_input())
    for _ in xrange(T):
        N = int(raw_input())
        print go(1, N)
    