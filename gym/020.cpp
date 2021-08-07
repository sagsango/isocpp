
#include <iostream>
using namespace std;



// TODO: page 22 of book -> C++ Design Generic Programming and design pattern
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
template< typename T, typename X, template <typename,typename> typename C >
class hi: public C<T,X>{
	public:
		void print(){
			cout << "Hello" << endl;
		}
};


// TODO: instantiation
template< template <typename,typename> typename C>
class hi<int,int,C>: public C<int,int> {
	public:
	void print(){
			cout << "Hi There!" << endl;
		}

};


int main(){
	hello<char,int> h;
	h.ft('a',1);
	h.fx(1);

	hi< int,int,hello> H;
	H.ft('a',1);
	H.fx(1);
	H.print();
}
