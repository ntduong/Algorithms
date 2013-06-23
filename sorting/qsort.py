from random import choice
def qsort(arr):
    if arr == []:
        return []
    else:
        pivot = choice(arr)
        arr.remove(pivot)
        smaller = qsort([x for x in arr if x  < pivot])
        bigger = qsort([x  for x in arr if x >= pivot])
        return smaller + [pivot] + bigger
        
if __name__ == '__main__':
    a = [4,3,2,1]
    sorted_a = qsort(a)
    print sorted_a