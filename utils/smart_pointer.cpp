/**
    Basic implementation of a smart pointer with reference count in C++
    Written by Duong Nguyen

    Todo: Provide testcases
    Note: Header and implementation should be separated.
*/

#include<iostream>
#include<string>
#include<memory>

using namespace std;

// HEADER
template<typename T> class SmartPointer {
public:
    explicit SmartPointer();
    explicit SmartPointer(T* memory);
    SmartPointer(const SmartPointer& other);
    SmartPointer& operator=(const SmartPointer& other);
    ~SmartPointer();

    T& operator * () const;
    T* operator -> () const;
    T* get() const;
    size_t get_share_cnt() const;
    void reset(T* new_memory);

private:
    struct Intermediary {
        T* resource;
        size_t ref_cnt;
    };

    Intermediary* data;

    void detach();
    void attach(Intermediary* to);

};

// IMPLEMENTATION

template<typename T> SmartPointer<T>::SmartPointer() {

    data = new Intermediary;
    data->resource = NULL;
    data->ref_cnt = 0;
}

template<typename T> SmartPointer<T>::SmartPointer(T* memory) {

    data = new Intermediary;
    data->resource = memory;
    data->ref_cnt = 1;
}

template<typename T> SmartPointer<T>::~SmartPointer() {
    detach();
}

template<typename T> T& SmartPointer<T>::operator * () const {
    return *(data->resource);
}

template<typename T> T* SmartPointer<T>::operator -> () const {
    return data->resource;
}

template<typename T> void SmartPointer<T>::detach() {
    --data->ref_cnt;
    if(data->ref_cnt == 0){
        delete data->resource;
        delete data;
    }
}

template<typename T> void SmartPointer<T>::attach(Intermediary* to){
    data = to;
    ++data->ref_cnt;
}

template<typename T> SmartPointer<T>::SmartPointer(const SmartPointer& other){
    attach(other.data);
}

template<typename T> SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer& other){
    // Don't forget to handle self-assignment and multiple assignments
    if(this != &other){
        detach();
        attach(other.data);
    }
    return *this;
}

template<typename T> T* SmartPointer<T>::get() const {
    return data->resource;
}

template<typename T> size_t SmartPointer<T>::get_share_cnt() const {
    return data->ref_cnt;
}

template<typename T> void SmartPointer<T>::reset(T* new_memory) {

    detach();
    data = new Intermediary;
    data->resource = new_memory;
    data->ref_cnt = 1;
}

struct Test {
    SmartPointer<Test> next;
};

/*
struct Test {
    shared_ptr<Test> next;
};
*/

int main(){

    SmartPointer<Test> a(new Test);
    SmartPointer<Test> b(new Test);

    // Reference cycle situation!
    a->next = b;
    b->next = a;

    {
        SmartPointer<Test> aa(a);
        SmartPointer<Test> bb(b);
        cout << a.get_share_cnt() << " " << b.get_share_cnt() << endl;
    }

    // reference-counted smart pointer can not deal with the situation
    cout << a.get_share_cnt() << " " << b.get_share_cnt() << endl;

    /*
    shared_ptr<Test> a = make_shared<Test>();
    shared_ptr<Test> b = make_shared<Test>();
    a->next = b;
    b->next = a;
    cout << a.use_count() << " " << b.use_count() << endl;
    */

    return 0;
}
