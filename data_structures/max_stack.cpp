/**
    Modified stack that supports max operation which returns the maximum value in the current stack.
    Note: throw exception when trying to pop, peek, or max an empty stack.
    See <stdexcept> for more details on exception in C++
*/
#include<iostream>
#include<algorithm>
#include<stack>
#include<stdexcept>

using namespace std;

template<typename T>
class MaxStack {
public:
    bool empty() const {
        return m_data.empty();
    }

    const T& max() const {
        if(!empty()){
            return m_data.top().second;
        }
        throw length_error("empty stack");
    }

    void push(const T& x){
        if(empty()){
            m_data.push(make_pair(x, x));
        } else{
            m_data.push(make_pair(x, std::max(x, m_data.top().second)));
        }
    }

    T pop() {
        if(empty()) {
            throw length_error("empty stack");
        }
        T ret = m_data.top().first;
        m_data.pop();
        return ret;
    }

    T peek() const {
        if(empty()) {
            throw length_error("empty stack");
        }
        return m_data.top().first;
    }

private:
    stack<pair<T,T>> m_data;
};

int main(){

    return 0;
}

