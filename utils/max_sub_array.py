""" Finding the sub-array containing contiguous elements that have which has largest sum."""
import sys

def slow(a):
    """ O(n^2) solution."""
    n = len(a)
    b = [0]
    for i in xrange(n):
        b.append(b[i]+a[i])
    # Now, b is array of cumulative sums of array a
    # b[i] := a[0]+..+a[i-1] = sum of the first i elements of a. Note that b[0] = 0
    
    ans = a[0]
    # Test all a[i..j] (inclusive)
    for i in xrange(n):
        for j in xrange(i,n):
            tmp = b[j+1] - b[i]
            if tmp > ans:
                ans = tmp
    return ans

def not_too_slow(a):
    """ O(nlogn) solution using divide and conquer approach."""
    n = len(a)
    if n == 1:
        return a[0]
    mid = n/2
    first_half = not_too_slow(a[0:mid])
    second_half = not_too_slow(a[mid:])
    
    le, ri = a[mid-1], a[mid]
    tmp = 0
    for j in xrange(mid-1, -1, -1):
        tmp += a[j]
        if tmp > le: 
            le = tmp
            
    tmp = 0
    for j in xrange(mid, n):
        tmp += a[j]
        if tmp > ri:
            ri = tmp
        
    return max(first_half, second_half, le+ri)
    
def fast(a):
    """ O(n) solution using linear scanning."""
    ans = -sys.maxint-1
    tmp = 0
    for v in a:
        tmp = tmp + v if tmp >= 0 else v
        ans = max(ans, tmp)
    return ans

if __name__ == '__main__':
    tc = [[-1,-2,-3], [1,2,3], [-2,1,-3,4,-1,2,1,-5,4], [0,-1,1,2], [1]]
    for a in tc:
        assert len(a) > 0, "Empty array!"
        assert slow(a) == not_too_slow(a) == fast(a), "Failed test " + a.__repr__()
        print fast(a)
    