#include <iostream>
#include <string>

using namespace std;

template< typename T, typename W>
void solve( T a, W b ){
	cout << "1" << endl;
}

// TODO: partial specialization of function not allowed
template< typename T>
void solve<T,int>( T a, int b){
	cout << "2" << endl;
}


int main(){
	solve<int,int>(1,2);
	solve<string,int>("hello",2);
	solve<string,string>("hello","World");
	solve<char,char>('A','a');
}
