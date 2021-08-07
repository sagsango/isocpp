
#include <iostream>
#include <memory>

// Works

class A;

class B{
public:
    B(){
        std::cout << "Constructor" << std::endl;
    }
    ~B(){
        std::cout << "Distructor" << std::endl;
    }
    void msg(){
        std::cout << "Im in B!" << std::endl;
        A *a; // NO Object yes assigned
    }
};

class A{
public:
    A(){
        std::cout << "Constructor" << std::endl;
    }
    ~A(){
        std::cout << "Distructor" << std::endl;
    }
    void msg(){
        std::cout << "Im in A!" << std::endl;
        B b; // Object has assigned
        b.msg();
    }
};


int main(){
    std::shared_ptr<A> ptr = std::make_shared<A>();
}


