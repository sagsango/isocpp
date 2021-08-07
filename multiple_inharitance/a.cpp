#include <iostream>
using namespace std;
class A{
public:
    int x, y;
    A(int x,int y):x(x),y(y)
    {
    
    }
};
class B{
public:
    int z;
    B(int z):z(z)
    {
    
    }
};
class C: public A, public B{
public:
    int w;
    C(int x,int y,int z,int w):A(x,y),B(z),w(w)
    {
    
    }
};
int main(){
    C c(1,2,3,4);
    cout << c.x <<" "<< c.y <<" "<< c.z <<" "<< c.w << endl;
}
