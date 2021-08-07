
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
    
        {
            std::unique_ptr<A> cpPtr = myPtr;
            
        }
        // give error here becsue distructor will be called 2nd time here
    
    }
}
