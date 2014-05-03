""" Rule-based punctuation correction: Stupid solution :)). """
import re

L1 = ['a', 'an', 'the', 'time', 'in', 'at', 'of', 'on', 'above', 'below', 'what', 'where', 'when', 'who', 'become', 'had', 'gotten', 'gone', 'seen', 'been']

def correct(sent):
    tokens = sent.split()
    n = len(tokens)
    start = 0

    while 1:
        try:
            i = tokens.index("???", start)
            if i < n-1:
                next_w = tokens[i+1]
                if next_w in L1 or next_w.endswith('ing') or next_w.endswith('ed'):
                    tokens[i] = "it's"
                else:
                    tokens[i] = "its"
            else:
                tokens[i] = "its"
            start = i+1
        except ValueError:
            break
        
    return ' '.join(tokens)
    
if __name__ == '__main__':
    N = int(raw_input())
    sents = []
    for _ in xrange(N):
        sents.append(raw_input().strip())
    
    for sent in sents:
        print correct(sent)