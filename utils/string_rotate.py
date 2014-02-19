""" Given two string A, B. Check if A is a rotation of B using only one substring test.
    E.g: B = xy, then a rotation of B is yx.
    Easy solution: B = xy, then BB = xyxy, just check if A is a substring of BB! 
"""

def check_rotation(A, B):
    C = "".join([B,B])
    return C.find(A) != -1
    
if __name__ == '__main__':
    assert check_rotation("12345", "34512") == True, "Wrong answer!"