
#include <iostream>
#include <memory>

class A{
public:
    int x,y;
    A(){
        std::cout << "A::Constructor" << std::endl;
    }
    ~A(){
        std::cout << "A::Distructor" << std::endl;
    }
    void msg()const{
        std::cout << "A::Hello! I am alive!" << std::endl;
    }
};
class B{
public:
    int x,y;
    B(){
        std::cout << "B::Constructor" << std::endl;
    }
    B(class A ob){
        ob.msg();
        std::cout << "B::Constructor" << std::endl;
    }
    ~B(){
        std::cout << "B::Distructor" << std::endl;
    }
    void msg()const{
        std::cout << "B::Hello! I am alive!" << std::endl;
    }
};

class C{
public:
    std::unique_ptr< int > x, y;
    C(int X,int Y){
        x = std::make_unique<int>();
        y = std::make_unique<int>();
        *x = X;
        *y = Y;
        std::cout << "C::Constructor" << std::endl;
    }
    ~C(){
        std::cout << "C::Distructor" << std::endl;
    }
};

class D{
public:
    int x, y;
    D(int x,int y):x(x),y(y){
        std::cout << "D::Constructor" << std::endl;
    }
    ~D(){
        std::cout << "D::Distructor" << std::endl;
    }
};

int main(){
    
    { // stack memory how get freed :: see
        std::unique_ptr<A> myPtr;
        myPtr = std::make_unique<A>();
    
        std::unique_ptr<A> cpPtr = std::make_unique<A>(*myPtr); // default copy constructor
    
        myPtr->msg();
        cpPtr->msg();
    
        std::unique_ptr<B> bPtr = std::make_unique<B>(*myPtr); // overloed : constructor
        bPtr->msg();
        
        std::unique_ptr<C> cPtr = std::make_unique<C>(10,20);
        //std::unique_ptr<C> ccpPtr = std::make_unique<C>(*cPtr); // Beacue smart pointer even are not deep copy constructor, so will give compile time error
        
        std::unique_ptr<D> dPtr = std::make_unique<D>(10,20);
        std::unique_ptr<D> dcpPtr = std::make_unique<D>(*dPtr); // Beacue smart pointer will find no need of deep copy so will work
    }
}
