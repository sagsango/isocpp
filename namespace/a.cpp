#include <iostream>
namespace A{
    int x = 1, y = 2;
    std::string s="Inside A";
}
namespace B{
    int x = 10, y = 20;
    std::string s="Inside B";
    
    namespace C{
        int x = 100, y = 200;
        std::string s="Inside C";
    }
}

int main(){
    std::cout << A::x <<" "<< A::y <<" "<< A::s << std::endl;
    std::cout << B::x <<" "<< B::y <<" "<< B::s << std::endl;
    std::cout << B::C::x <<" "<< B::C::y <<" "<< B::C::s << std::endl;
    return 0;
}
