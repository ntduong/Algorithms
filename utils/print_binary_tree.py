 class BinaryTree:
	def __init__(self, depth, value=0):
		self.value = value
		self.left = BinaryTree(depth-1, value*2 + 1) if depth > 0 else None
		self.right = BinaryTree(depth-1, value*2 + 2) if depth > 0 else None
		
	def __str__(self, depth=0):
		ret = ""
		
		if self.right:
			ret += self.right.__str__(depth+1)
		
		ret += "\n" + ("   "*depth) + str(self.value)
		
		if self.left:
			ret += self.left.__str__(depth+1)
			
		return ret
		
if __name__ == '__main__':
	print BinaryTree(4)