
#include <iostream>
#include <memory>

int main(){
    std::shared_ptr<A> ptr = std::make_shared<A>();
}
class A{
public:
    A(){
        std::cout << "Constructor" << std::endl;
    }
    ~A(){
        std::cout << "Distructor" << std::endl;
    }
};
