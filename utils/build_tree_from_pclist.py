""" Build a tree from given list of (child, parent) edges. """

from collections import defaultdict
import json
import random

def gen_tree_edges(n_nodes):
    """ Randomly generate tree edges."""
    
    id_pool = range(n_nodes)
    random.shuffle(id_pool)
    root = id_pool.pop()
    
    first_child = id_pool.pop()
    edges = [[first_child, root]]
    while len(id_pool) != 0:
        if random.random() > .1: # add child
            edges.append([id_pool.pop(), random.choice(edges)[0]])
        
        else: # add sibling
            edges.append([id_pool.pop(), random.choice(edges)[1]])
            
    random.shuffle(edges)
    return edges
    
def build_tree(edges):
    """ Build tree from list of edges."""
    
    trees = defaultdict(dict)
    
    for child, parent in edges:
        trees[parent][child] = trees[child]
    
    children, parents = zip(*edges)
    roots = set(parents).difference(children)
    
    return {root: trees[root] for root in roots}
    
def test(n_nodes=10):
    
    edges = gen_tree_edges(n_nodes)
    print "edges {}".format(edges)
    print json.dumps(build_tree(edges), indent=1)
    
if __name__ == "__main__":
    test()
    