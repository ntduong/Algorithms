'''
Created on 2013/01/22
@author: duong
@see: http://www.mblondel.org/journal/2009/08/31/dynamic-time-warping-theory
A simple implementation of Dynamic Time Warpping algorithm.
'''

class DTW(object):
    def __init__(self, seq1, seq2, distance_func=None):
        '''
        seq1, seq2 are two lists,
        distance_func is a function for calculating the local distance between two elements.
        '''
        self._seq1 = seq1
        self._seq2 = seq2
        self._distance_func = distance_func if distance_func else lambda: 0
        
        # memo table to save DTW distances: (i,j) <-> DTW_dist(seq1[:i], seq2[:j])
        self._map = {(-1,-1) : 0.0} 
        
        # memo table to save local distances between two elements, i from seq1, j from seq2
        self._distance_matrix = {} 
        
        self._path = []
        
    def get_distance(self, i1, i2):
        ret = self._distance_matrix.get((i1,i2))
        if not ret:
            ret = self._distance_func(self._seq1[i1], self._seq2[i2])
            self._distance_matrix[(i1,i2)] = ret
        return ret
    
    def calculate_backward(self, i1, i2):
        '''
        Calculate the DTW distance between seq1[:i1+1] and seq2[:i2+1]
        '''
        if self._map.get((i1,i2)) is not None:
            return self._map[(i1,i2)]
        
        if i1 == -1 or i2 == -1:
            self._map[(i1,i2)] = float('inf')
            return float('inf')
        
        # recursive + memoization = DP
        min_i1, min_i2 = min((i1-1,i2),(i1,i2-1),(i1-1,i2-1), key=lambda x: self.calculate_backward(*x))
        
        self._map[(i1,i2)] = self.get_distance(i1, i2) + self.calculate_backward(min_i1, min_i2)
        
        return self._map[(i1,i2)]
    
    def calculate_DTW_distance(self):
        return self.calculate_backward(len(self._seq1) - 1, len(self._seq2) - 1)
    
    def get_path(self):
        '''
        Get the DTW path for two sequences seq1, seq2.
        Must be called after calculate_DTW_distance.
        '''
        i1, i2 = (len(self._seq1) - 1, len(self._seq2) - 1)
        while (i1, i2) != (-1, -1):
            self._path.append((i1,i2))
            min_i1, min_i2 = min((i1-1, i2), (i1, i2-1), (i1-1, i2-1),
                                 key = lambda x: self._map[(x[0],x[1])])
            i1,i2 = min_i1, min_i2
            
        return self._path

if __name__ == '__main__':
    # Test DTW class
    from math import fabs
    myDTW = DTW([1,2,3,4,6], [1,2,3,5], distance_func = lambda x,y: fabs(x-y))
    print myDTW.calculate_DTW_distance()
    for i1,i2 in reversed(myDTW.get_path()):
        print '%d <-> %d: %f' %(myDTW._seq1[i1], myDTW._seq2[i2], fabs(myDTW._seq1[i1]-myDTW._seq2[i2]))
        