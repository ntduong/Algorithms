/**
    Simple implementation of bit vector in C++
    Written by Duong Nguyen
    Email: ntduong268(@)gmail.com
*/

#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstdlib>

using namespace std;

class BitVec {
private:
    int *arr;
    size_t sz;
    static size_t DEFAULT_SIZE;
    static const size_t BYTE_SIZE = 8;
    static const size_t BLOCK_SIZE = sizeof(int) * BYTE_SIZE;

public:
    BitVec():sz(DEFAULT_SIZE){
        arr = new int[DEFAULT_SIZE];
    }

    BitVec(size_t n):sz(n){
        arr = new int[n];
    }

    virtual ~BitVec(){
        if(arr != NULL){
            delete[] arr;
            arr = NULL;
        }
        sz = 0;
    }

    int length() const {
        return BLOCK_SIZE * sz;
    }

    void initialize(){
        for(size_t i = 0; i < sz; ++i){
            arr[i] = 0;
        }
    }

    // Clear bit at given index idx
    bool clear_bit(size_t idx){
        if(idx < 0 || idx >= length()) {
            cerr << "Invalid index: Out of range";
            return false;
        }

        // Get 32-bit block index
        int bid = idx / BLOCK_SIZE;

        // Next, get index inside the block
        int id = idx % BLOCK_SIZE;
        //int id = (idx & 0x1F); // work in case an int = 32 bits

        arr[bid] &= ~(1 << id);

        return (arr[bid] & (1 << id)) == 0;
    }

    bool test_bit(size_t idx) const {
        if(idx < 0 || idx >= length()) {
            cerr << "Invalid index: Out of range";
            return false;
        }

        int bid = idx / BLOCK_SIZE;
        int id = idx % BLOCK_SIZE;
        return (arr[bid] & (1 << id)) != 0;
    }

    bool set_bit(size_t idx){
        if(idx < 0 || idx >= length()) {
            cerr << "Invalid index: Out of range";
            return false;
        }

        int bid = idx / BLOCK_SIZE;
        int id = idx % BLOCK_SIZE;
        arr[bid] |= (1 << id);

        return (arr[bid] & (1 << id)) != 0;
    }

    void show() const {
        for(size_t i = 0; i < length(); ++i){
            if(test_bit(i)) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }
};

size_t BitVec::DEFAULT_SIZE = 100;


void test_bed(int n, int n_trials){
    BitVec m_BV(n);
    m_BV.initialize();
    int length = m_BV.length();
    cout << "Initial bitvec:\n";
    m_BV.show();

    srand((unsigned)time(NULL));
    cout << "Set random bits...\n";
    vector<int> ids;
    for(int i = 0; i < n_trials; ++i){
        int id = rand() % length;
        ids.push_back(id);
        cout << "Set bit " << id << ":\n";
        m_BV.set_bit(id);
        m_BV.show();
    }

    cout << "Clear set bits...\n";
    for(auto id : ids){
        if(m_BV.test_bit(id)){
            cout << "Clear bit " << id << ":\n";
            m_BV.clear_bit(id);
        }
    }

    m_BV.show();

    cout << "Test out of range...\n";
    m_BV.set_bit(length+2);

}

int main(){
    test_bed(4,5);
    return 0;
}
