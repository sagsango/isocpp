
#include <iostream>
using namespace std;

template< typename T, typename X>
class hello{
	public:
		T a;
		X b;
		hello(){
			cout <<"hello() :"<< typeid(T).name() <<" "<< typeid(X).name() << endl;
		}
		void ft( T p, X q ){
			cout << p <<" "<< q << endl;
		}
		void fx( X p ){
			cout << p << endl;
		}
};


// TODO: class base name is typename
template< typename C>
class hi: public C{
	public:
		void print(){
			cout << "Hello" << endl;
		}
};



template< typename T>
class hi<hello<int,T>>: public hello<int,T> {
	public:
	void print(){
			cout << "Hi There!" << endl;
		}

};


int main(){
	hello<char,int> h;
	h.ft('a',1);
	h.fx(1);

	hi<hello<int,int>> H;
	H.ft('a',1);
	H.fx(1);
	H.print();

}
