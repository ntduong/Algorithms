# Knuth or Fisher-Yates shuffle algorithm

from random import randint
def shuffle(a):
	n = len(a)
	if n <= 1: return a
	for i in xrange(n-1,-1,-1):
		j = randint(0, i)
		a[i],a[j] = a[j],a[i] # swap		
	return a

if __name__ == '__main__':
	a = [1,2,3,4]
	print shuffle(a)

	
	