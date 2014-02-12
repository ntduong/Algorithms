""" Simple implementation of skiplist.
	
	Skiplist is a probabilistic data structure, invented by W.Pugh 
	that allows efficient search, insertion, and removal operations
	Time complexity: O(log(n)) with high probability. 	
	cf. Balanced tree (e.g. AVL tree, Red-black tree, splay tree, etc.)
	See the paper www.cl.cam.ac.uk/teaching/2005/Algorithms/skiplists.pdf for more details
	
	Written by Duong Nguyen
"""

import random

class SkipNode:
	""" Skiplist's node class"""
	
	def __init__(self, height=0, value=None):
		self.value = value
		self.height = height
		self.next = [None] * height
		
class SkipList:
	""" Skiplist class with basic look up, insert, removal operations"""
	
	def __init__(self):
		self.head = SkipNode()
		self.max_height = 0
		self.len = 0
		
	def __len__(self):
		return self.len
	
	def random_height(self):
		""" Generate random height for a new node."""
		
		height = 1
		while random.randint(1,2) != 1:
			height += 1
		
		return height
	
	def helper(self, val):
		""" Traverse the skiplist from top to bottom level, 
			return a list of nodes having the largest values, 
			which are smaller than val in each level.
		"""
		
		before_nodes = [None] * self.max_height
		x = self.head
		
		for i in reversed(xrange(self.max_height)): # iterate from top level to bottom level
			while (x.next[i] != None) and (x.next[i].value < val): # iterate i-th level
				x = x.next[i]
			before_nodes[i] = x
			
		return before_nodes
	
	def look_up(self, val, before_nodes=None):
		if before_nodes == None:
			before_nodes = self.helper(val)
		
		# 0-level is the bottom level, containing all of the current values in the skiplist
		if len(before_nodes) > 0:
			candidate = before_nodes[0].next[0]
			if (candidate != None) and (candidate.value == val):
				return candidate
				
		return None
		
	def insert(self, val):
		""" Insert a new node with value val if it is NOT in the skiplist yet."""
		
		new_node = SkipNode(self.random_height(), val)
		
		# Update skiplist max_height
		self.max_height = max(self.max_height, new_node.height)
		while len(self.head.next) < self.max_height:
			self.head.next.append(None)
		
		before_nodes = self.helper(val)
		if self.look_up(val, before_nodes) == None:
			for i in xrange(len(new_node.next)): # insert in each level
				new_node.next[i] = before_nodes[i].next[i]
				before_nodes[i].next[i] = new_node 
			
			self.len += 1
			
	def remove(self, val):
		""" Remove a node with given value val."""
		
		before_nodes = self.helper(val)
		x = self.look_up(val, before_nodes)
		if x != None:
			for i in reversed(xrange(len(x.next))):
				before_nodes[i].next[i] = x.next[i]
				if self.head.next[i] == None: # reduce skiplist's height if necessary
					self.max_height -= 1
			
			self.len -= 1
		else:
			print "%d not found" % val
			
	
	def show(self):
		""" Print the skiplist from the top to bottom levels."""
		
		for i in xrange(len(self.head.next)-1,-1,-1):
			x = self.head
			while x.next[i] != None:
				print x.next[i].value,
				x = x.next[i]
			print ''
				
if __name__ == "__main__":
	random.seed(0)
	m_Test = SkipList()
	lo, hi = 0, 100
	for i in xrange(10):
		m_Test.insert(random.randint(lo,hi))
	
	m_Test.show()
	