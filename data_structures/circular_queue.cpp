#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>

using namespace std;

template<typename T>
class Queue {
private:
    vector<T> data;
    size_t head, tail, cnt;

public:
    explicit Queue(size_t cap) : head(0), tail(0), data(cap){}

    void enqueue(const T& x){
        if(cnt == data.size()){
            rotate(data.begin(), data.begin()+head, data.end());
            head = 0;
            tail = cnt;
            data.resize(data.size() << 1); // double the capacity
        }

        data[tail] = x;
        cnt++;
        tail = (tail+1) % data.size();
    }

    T dequeue() {
        if(cnt){
            cnt--;
            T ret = data[head];
            head = (head+1) % data.size();
            return ret;
        }
        throw length_error("empty queue");
    }

    size_t size() const {
        return cnt;
    }

};

int main(){

    return 0;
}
