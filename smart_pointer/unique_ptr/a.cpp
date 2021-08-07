
#include <iostream>
#include <memory>

class A{
public:
    int x,y;
    A(){
        std::cout << "Constructor" << std::endl;
    }
    ~A(){
        std::cout << "Distructor" << std::endl;
    }
};
int main(){
    
    {
        std::unique_ptr<A> myPtr;
        myPtr = std::make_unique<A>();
    
    
    }
}
