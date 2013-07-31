/**
    Animal Queue @3.7 CTCI
    Study note:
    - OOP in C++ (inheritance, virtual methods, etc)
    - Casting (dynamic_cast, etc)
    - how to do (a instanceof Type -- in Java) in C++
    - isinstance in Python

    (c) Duong Nguyen
    Email: ntduong268(@)gmail.com
*/

#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<list>

using namespace std;

class Animal{
    int timestamp;
    string name;
public:
    Animal(string name):name(name), timestamp(-1){}

    void set_ts(int ts){
        timestamp = ts;
    }

    int get_ts() const{
        return timestamp;
    }

    bool is_older_than(const Animal& o){
        return timestamp < o.get_ts();
    }

    virtual void print(){
        cout << name << "\n";
    }
};

class Dog : public Animal{
public:
    Dog(string name) : Animal(name){}
    virtual void print(){
        cout << "Dog ";
        Animal::print();
    }
};

class Cat : public Animal{
public:
    Cat(string name) : Animal(name){}
    virtual void print(){
        cout << "Cat ";
        Animal::print();
    }
};

class AnimalQueue{
    list<Dog*> dogs;
    list<Cat*> cats;
    int ts;
public:
    AnimalQueue():ts(0){}

    bool empty_dogs(){
        return dogs.empty();
    }

    bool empty_cats(){
        return cats.empty();
    }

    bool empty_animals(){
        return empty_dogs() && empty_cats();
    }

    void enqueue(Animal *a){
        a->set_ts(ts);
        ts++;
        // Use dynamic_cast as isinstanceof in Java?
        // Is there any better way?
        Dog *d = dynamic_cast<Dog*>(a);
        Cat *c = dynamic_cast<Cat*>(a);

        if(c){
            cats.push_back(c);
        }
        else if(d){
            dogs.push_back(d);
        }
        else{
            cerr << "Something wrong!";
            exit(1);
        }
    }

    Animal *dequeueAny(){
        if(dogs.empty()){
            return dequeueCats();
        }
        else if(cats.empty()){
            return dequeueDogs();
        }
        else{
            Cat *c = cats.front();
            Dog *d = dogs.front();
            if(c->get_ts() < d->get_ts()){
                return dequeueCats();
            }
            else{
                return dequeueDogs();
            }
        }
    }

    Dog *dequeueDogs(){
        Dog *ret = dogs.front();
        dogs.pop_front();
        return ret;
    }

    Cat *dequeueCats(){
        Cat *ret = cats.front();
        cats.pop_front();
        return ret;
    }
};

int main(){
    Animal *a = new Cat("Cathy");
    Animal *b = new Dog("Dummy");
    Animal *c = new Cat("Cute2");
    Animal *d = new Dog("Doom");
    AnimalQueue aq;
    aq.enqueue(a);
    aq.enqueue(b);
    aq.enqueue(d);
    aq.enqueue(c);

    while(!aq.empty_animals()){
        Animal *e = aq.dequeueAny();
        e->print();
    }

    delete a;
    delete b;
    delete c;
    delete d;

    return 0;
}
