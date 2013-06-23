'''
Created on 2013/02/11
@author: duong
@note: Trie-based auto complete demo.
       We can customize Node structure to provide more features.
'''

import os.path

class Node(object):
    def __init__(self):
        self.next = {}
        self.word_marker = False
        
    def add_item(self, item):
        """
        Add new item (string, etc) to trie.
        """
        
        if len(item) == 0:
            self.word_marker = True
            return
        
        first = item[0]
        item = item[1:]
        
        if self.next.has_key(first):
            self.next[first].add_item(item)
        else:
            node = Node()
            self.next[first] = node
            node.add_item(item)
            
    def dfs(self, sofar=None):
        if self.next.keys() == []:
            print 'Match:', sofar
            return
        
        if self.word_marker == True:
            print 'Match:', sofar
            
        for key in self.next.keys():
            self.next[key].dfs(sofar + key)
            
    def search(self, item, sofar=""):
        if len(item) > 0:
            key = item[0]
            item = item[1:]
            if self.next.has_key(key):
                sofar = sofar + key
                self.next[key].search(item, sofar)
            else:
                print 'No match'
                
        else:
            if self.word_marker == True:
                print 'Match:', sofar
                
            for key in self.next.keys():
                self.next[key].dfs(sofar + key)
                
class AutoComplete(object):
    def __init__(self):
        self.dictfiles = []
        self.root = None
        
    def build_or_update_Trie(self, filename):
        """
        Parse input dictionary file, and build/update the trie.
        Here, input dict file has the following format:
            word1
            word2
            ...
            wordn
        """    
        
        print 'Starting build/update trie...'
        if self.root == None:
            self.root = Node()
            
        with open(filename, "rt") as f:
            for line in f.readlines():
                self.root.add_item(line.strip())
    
        self.dictfiles.append(filename)        
        print 'Finished!'
    
    
                
    def search(self, keyword):
        self.root.search(keyword)
        
    def __getstate__(self):
        """
        Return state values to be pickled.
        """
        return self.root, self.dictfiles
    
    def __setstate__(self, state):
        """
        Restore state from the unpickled state values.
        """
        self.root, self.dictfiles = state
                
def main(pickledFile='auto.pkl', dictfile='dict.txt'):
    """
        Demo autocomplete.
    """               
    try:
        import cPickle as pickle
    except ImportError, err:
        print err
        import pickle  
        
    if os.path.exists(pickledFile) and os.path.isfile(pickledFile):
        with open(pickledFile, 'rb') as f:
            ac = pickle.load(f)
    else:
        ac = AutoComplete()
        ac.build_or_update_Trie(dictfile)
        
    word = raw_input("Please enter a search word:")
    ac.search(word)
    
    with open(pickledFile, 'wb') as f:
        pickle.dump(ac, f)
        
def test(word, mydict='mydict.txt'):
    ac = AutoComplete()
    ac.build_or_update_Trie(mydict)
    ac.search(word)
      
if __name__ == '__main__':
    #test('ef')
    main()