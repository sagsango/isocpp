
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
    std::shared_ptr<A> ptr = std::make_shared<A>();
}
