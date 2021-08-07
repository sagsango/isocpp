
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
    {
        std::shared_ptr<A> ptr1;
        ptr1 = std::make_shared<A>();
        {
            std::shared_ptr<A> ptr2 = ptr1;
            {
                std::shared_ptr<A>ptr3 = ptr1;
            }
        }
    }
}
