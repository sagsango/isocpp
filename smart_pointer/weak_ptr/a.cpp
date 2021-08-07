
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
    
    std::weak_ptr<A> wPtr;
    {
        std::cout << "Before declaration of shared ptr" << std::endl;
        std::shared_ptr<A> sPtr = std::make_shared<A>();
        std::cout << "After declaration of shared ptr" << std::endl;
    }
    std::cout << "Going to return from main" << std::endl;
    return 0;
}
