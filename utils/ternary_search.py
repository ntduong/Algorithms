# Consider the problem of finding the maximum value of an unimodal function f(x) on some interval [L,R]
# Take any two points m1, m2 in this segment: L < m1 < m2 < R.
# We have some observations as below (check out the def of unimodal function to understand more!!)
# f(m1) < f(m2): update L = m1 --> consider [m1,R], because the maximum value don't lie in [L,m1], we don't need to care [L,m1]
# f(m1) > f(m2): update R = m2 --> consider [L,m2], because the maximum value don't lie in [m2,R], we don't need to care [m2,R]
# f(m1) == f(m2): update L = m1, R = m2 --> consider [m1, m2]
# How to choose m1, m2: Let take some a in (0,1/2)(? see the explanation below)
# m1 = L+a(R-L) = aR + (1-a)L
# m2 = R-a(R-L) = (1-a)R +  aL
# For m1 < m2: L+a(R-L) < R-a(R-L) -> 2a(R-L) < R-L --> a < 1/2
# Check out Wikipedia for more details.
# We can do the same to find the minumum value of an unimodal function f(x) on some interval [L,R]

# In the implementation below, I use a = 1/3
# O(logn) algorithm
# T(n) = T(2/3*n) + C --> O(logn)

def ternarySearch(f, left, right, epsilon):
    if right-left < epsilon:
        return (left + right) / 2
    
    m1 = (2*left+right)/3
    m2 = (left+2*right)/3
    
    if f(m1) < f(m2):
        return ternarySearch(f, m1, right, epsilon)
    elif f(m1) > f(m2):
        return ternarySearch(f, left, m2, epsilon)
    else: return ternarySearch(f, m1, m2, epsilon)
    
# See binary search, bisection algorithm, etc for similar ideas