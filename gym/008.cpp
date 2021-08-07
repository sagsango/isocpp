
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

// TODO: partial specialization of class is allowed
template< typename T>
class hello<T,int>{
	public:
		T a;
		int b;
		void ft( T p, int q){
			cout << " Hello "<< endl;
		}
		void fx( int p){
			cout <<" World"  << endl;
		}
};

int main(){
	hello<char,int> h;
	h.ft('a',1);
	h.fx(1);
}
