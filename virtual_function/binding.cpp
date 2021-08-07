#include <iostream>
#include <memory>
using namespace std;
class A{
public:
    A(){
        std:: cout << "A()" << std:: endl;
    }
    virtual void msg()  = 0;
    virtual ~A(){
        std:: cout << "~A()" << std:: endl;
    }
};
class B:public A{
public:
    B(){
        std:: cout << "B()" << std:: endl;
    }
    void msg()override{
        std:: cout << "Msg from B" << std::endl;
    }
    virtual ~B(){
        std:: cout << "~B()" << std:: endl;
    }
};
class C:public A{
public:
    C(){
        std:: cout << "C()" << std:: endl;
    }
    void msg()override{
        std:: cout << "Msg from C" << std::endl;
    }
    virtual ~C(){
        std:: cout << "~C()" << std:: endl;
    }
};
int main(){
    std::unique_ptr<A> b = std::make_unique<B>();
    std::unique_ptr<A> c = std::make_unique<C>();
    b->msg();
    c->msg();
}
