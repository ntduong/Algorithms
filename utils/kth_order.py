"""
    Find k-th smallest element from an unsorted array
"""

from random import choice

def kth_smallest(arr, k):
    if not arr: 
        return None
    sz = len(arr)
    assert k <= sz, "k should not be greater than size of array."
    
    if len(arr) == 1:
        return arr[0]
    
    pivot = choice(arr)
    smaller = [x for x in arr if x < pivot]
    equal = [x for x in arr if x == pivot]
    bigger = [x for x in arr if x > pivot]
    
    if k <= len(smaller):
        return kth_smallest(smaller, k)
    elif len(smaller) < k <= len(smaller) + len(equal):
        return pivot
    else:
        return kth_smallest(bigger, k-len(smaller)-len(equal))
        
if __name__ == '__main__':
    arr = [10, 7, 2, 11, 4, 6, 3]
    print kth_smallest(arr, 4)
