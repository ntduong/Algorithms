""" Coin change 
	Given N >= 0, and a set A = {a_0,...,a_{M-1}}, a_i >= 0 for all i=0,M-1.
	How many ways can we express N as sum of elements in A? Note that, the order of a_i doesn't matter.
	In the DP solution below, state[n][m] := # ways that n is expressed as sum of elements in {a_0,...a_{m-1}} 
"""

def coin_change(N, a):
	""" DP solution, O(NxM) time, O(NxM) space.
		Note: we can reduce to O(N) space, using 1d-array.
	"""
	M = len(a)
	dp = [[0 for _ in xrange(M)] for _ in xrange(N+1)] # (N+1) x M 2d-array
	
	# Base case: n = 0, there is one way, using none element!
	for i in xrange(M):
		dp[0][i] = 1
		
	for i in xrange(1,N+1):
		for j in xrange(M):
			# count number of ways for i using a_j
			x = dp[i-a[j]][j] if i >= a[j] else 0
			
			# count number of ways for i not using a_j
			y = dp[i][j-1] if j >= 1 else 0
			
			dp[i][j] = x + y
			
	return dp[N][M-1]
			
def test():
	assert coin_change(4, [1,2,3]) == 4, "Failed test!"
	
if __name__ == '__main__':
	test()

