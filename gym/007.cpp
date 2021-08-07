#include <iostream>
using namespace std;

template< typename T, typename X>
class hello{
	public:
		T a;
		X b;
		void ft( T p ){
			cout << p << endl;
		}
		void fx( X p ){
			cout << p << endl;
		}
};

// TODO: partial specialization of class allowed
template< typename T>
class hello<T,int>{
	public:
		T a;
		int b;
		void ft( T p){
			cout << p << endl;
		}
		void fx( int p){
			cout << p << endl;
		}
};

int main(){
	hello<char,int> h;
	h.ft('a');
	h.fx(1);
}
