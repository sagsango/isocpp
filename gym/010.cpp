


#include <iostream>
using namespace std;

template< typename T>
void fun( T p){
	cout << " Hello " << endl;
}


// TODO: can change function structure during specialization
template<>
void fun<int>( int p){
	int x = 10;
	int y = 20;
	cout << x * y << endl;
}

int main(){
	fun<char>('a');
	fun<int>(1000);
}
