#include <iostream>
using namespace std;
class A{
public:
    virtual void f1(){
        cout << "Im in A" << endl;
    }
    void f2(){
        cout << "Im in A" << endl;
    }
};
class B:public A{
public:
    void f1(){
        cout << "Im in B" << endl;
    }
    void f2(){
        cout << "Im in B" << endl;
    }
};
int main(){
    A a;
    B b;
    a.f1();
    b.f1();
    a.f2();
    b.f2();
    
    A * ptr;
    
    ptr = new A;
    ptr->f1();
    ptr->f2();
    
    ptr = new B;
    ptr->f1();
    ptr->f2();
    
   
    
}
