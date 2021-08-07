#include <iostream>
#include <string>

using namespace std;

// resolvable
template< typename T, typename W >
bool smin( T& a, W b){
	if( a > b ){
		a = b;
		return true;
	}
	return false;
}

// resolvable
template< typename T, typename W >
bool smax( T& a, W b){
	if( a < b ){
		a = b;
		return true;
	}
	return false;
}

// non resolvable
template< typename T >
int mysize(){
	return sizeof( T );
}

int main(){
	int x = 10, y = 20;
	smax<int,int>(x,y);
	cout << x <<" "<< y << endl;

	char a = 'a', b = 'b';
	smax<char,char>(a,b);
	cout << a <<" "<< b << endl;

	float p = 10.2, q = 9.5;
	smin(p,q);
	cout << p <<" "<< p << endl;


	cout << mysize<int>() <<" "<< mysize<char>() << endl;


}


		
