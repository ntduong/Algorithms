#include<iostream>
#include<vector>
#include<cassert>
#include<fstream>
#include<algorithm>

using namespace std;
const int MAXSIZE = 9;
const int BOXSIZE = 3;
int f[MAXSIZE+1];

void print_sudoku(const vector<vector<int> >& A){
    for(int i = 0; i < A.size(); ++i){
        for(const auto& v: A[i]){
            cout << v << " ";
        }
        cout << endl;
    }
}

// Check initial configuration
bool is_valid_sudoku(const vector<vector<int> >& A){
    for(int i = 0; i < MAXSIZE; ++i){
        fill(f, f+MAXSIZE+1, 0);
        for(int j = 0; j < MAXSIZE; ++j){
            if(A[i][j] < 0 || A[i][j] > MAXSIZE) return false;
            f[A[i][j]]++;
            if(A[i][j] != 0 && f[A[i][j]] >= 2) return false;
        }
    }

    for(int i = 0; i < MAXSIZE; ++i){
        fill(f, f+MAXSIZE+1, 0);
        for(int j = 0; j < MAXSIZE; ++j){
            if(A[j][i] < 0 || A[j][i] > MAXSIZE) return false;
            f[A[j][i]]++;
            if(A[j][i] != 0 && f[A[j][i]] >= 2) return false;
        }
    }

    for(int I = 0; I < BOXSIZE; ++I){
        for(int J = 0; J < BOXSIZE; ++J){
            fill(f, f+MAXSIZE+1, 0);
            for(int a = 0; a < BOXSIZE; ++a){
                for(int b = 0; b < BOXSIZE; ++b){
                    int v = A[I*BOXSIZE+a][J*BOXSIZE+b];
                    if(v < 0 || v > MAXSIZE) return false;
                    f[v]++;
                    if(v != 0 && f[v] >= 2) return false;
                }
            }
        }
    }
    return true;
}

bool valid_to_add(vector<vector<int> >& A, int r, int c, int val){
    for(int j = 0; j < A[r].size(); ++j){
        if(A[r][j] == val) return false;
    }

    for(int i = 0; i < A.size(); ++i){
        if(A[i][c] == val) return false;
    }

    int I = r/BOXSIZE, J = c/BOXSIZE;
    for(int a = 0; a < BOXSIZE; ++a){
        for(int b = 0; b < BOXSIZE; ++b){
            if(A[I*BOXSIZE+a][J*BOXSIZE+b] == val) return false;
        }
    }

    return true;
}

bool solve_helper(vector<vector<int> >& A, int r, int c){
    if(c == A[r].size()){
        c = 0;
        if(++r == A.size()){
            return true;
        }
    }

    if(A[r][c] != 0){
        return solve_helper(A, r, c+1);
    }

    for(int val = 1; val <= MAXSIZE; ++val){
        if(valid_to_add(A, r, c, val)){
            A[r][c] = val;
            if(solve_helper(A, r, c+1)){
                return true;
            }
        }
    }

    A[r][c] = 0;
    return false;
}

bool solve(vector<vector<int> >& A){
    if(!is_valid_sudoku(A)) {
        cerr << "Initial configuration violates constraints.\n";
        return false;
    }

    if(solve_helper(A, 0, 0)){
        print_sudoku(A);
        return true;
    } else{
        cout << "No solution exists.\n";
        return false;
    }
}

void read_input(vector<vector<int> >& A, const string& fname){
    ifstream ifs(fname.c_str(), ios::in);
    string line;
    for(int i = 0; i < MAXSIZE; ++i){
        getline(ifs, line);
        assert(line.length() == MAXSIZE);
        for(int j = 0; j < MAXSIZE; ++j){
            A[i][j] = line[j]-'0';
        }
    }

    ifs.close();
}

int main(){

    vector<vector<int> > A(MAXSIZE, vector<int>(MAXSIZE, 0));
    read_input(A, "sudoku.txt");
    solve(A);
    return 0;
}
