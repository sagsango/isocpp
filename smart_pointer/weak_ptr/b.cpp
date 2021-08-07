
#include <iostream>
#include <memory>
class A{
public:
    A(){
        std::cout << "Constructor" << std::endl;
    }
    ~A(){
        std::cout << "Distructor" << std::endl;
    }
};
int main(){
    
    std::weak_ptr<A> wPtr = std::make_weak<A>();
    // there is no make_weak
    
    return 0;
}

