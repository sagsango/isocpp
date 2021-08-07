


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

// TODO: introduced new var in specialization
template<>
class hello<int,char>{
	public:
		int a;
		char b;
		int m_newvar = 0;
		void ft( int p, char q ){
			cout << " hello "<< endl;
		}
		void fx( char p ){
			cout << " ola " << endl;
		}
};


// TODO: change structure of whole class during specialization
template<>
class hello<int,int>{
	public:
		int a;
		char b;
		int m_newvar = 0;
		void ft( int p, char q , float y){
			cout << "Random "<< endl;
		}
		void fx( char p ){
			cout << " Name" << endl;
		}
		void fz(){
			cout << "Sagar" << endl;
		}
};




int main(){
	hello<char,int> h;
	h.ft('a',1);
	h.fx(1);

	hello<int,char> H;
	H.ft(1,'a');
	H.fx('a');
}
