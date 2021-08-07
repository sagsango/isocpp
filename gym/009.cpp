

#include <iostream>
using namespace std;

template< typename T, typename X>
class hello{
	public:
		T a;
		X b;
		void ft( T p, X q ){
			cout << p <<" "<< q << endl;
		}
		void fx( X p ){
			cout << p << endl;
		}
};


// TODO: partial specialization of function not allowed
template< typename T>
void hello<T,int>::ft( T p, int x){
	cout << " Hello " << endl;
}

int main(){
	hello<char,int> h;
	h.ft('a',1);
	h.fx(1);
}
