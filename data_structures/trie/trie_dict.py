'''
Created on 2013/02/11
@author: duong
'''

class Trie(object):
    
    def __init__(self):
        self.root = [None,{}]
        
    def add(self, key, value):
        cur_node = self.root
        for ch in key:
            cur_node = cur_node[1].setdefault(ch, [None,{}])
        cur_node[0] = value
        
    def find(self, key):
        cur_node = self.root
        for ch in key:
            try:
                cur_node = cur_node[1][ch]
            except KeyError:
                return None
        return cur_node[0]
    
    def find_prefix(self, key):
        cur_node = self.root
        remainder = key
        for ch in key:
            try:
                cur_node = cur_node[1][ch]
            except KeyError:
                return (cur_node[0], remainder)
            remainder = remainder[1:]
        return (cur_node[0], remainder)
    
    def convert(self, keystring):
        valuestring = []
        key = keystring
        while key:
            value, key = self.find_prefix(key)
            if not value:
                return (''.join(valuestring), key)
            valuestring.append(value)
        return (''.join(valuestring), key)
                    
def main(mydict='mydict.txt'):
    trie = Trie()
    with open(mydict, 'rt') as f:
        for line in f.readlines():
            key,value = line.strip().split(r':')
            #print "Add %s: %s" %(key,value)
            trie.add(key, value)
            
    '''
    # Look up a word in dict
    words = ['flo', 'duong', 'flower']
    for word in words:
        mean = trie.find(word)
        if mean is not None:
            print '%s: %s' %(word,mean)
    '''
                 
    # Look up a prefix
    value,key = trie.convert("flow")
    print value
    print key
    
    
if __name__ == '__main__':
    main()