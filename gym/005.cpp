#include <iostream>
#include <string>

using namespace std;

template< typename Type>
void fun(Type x){
	cout << "fun<" << typeid(x).name() << ">(Type)" << endl;
}

void fun(int x){
	cout << "fun(int)" << endl;
}

void fun(string x){
	cout << "fun(string)" << endl;
}

// TODO: see how string type is not resolvable by compiler, string with storage & without storage.
int main(){
	string x = "Hi Sagar!";
	fun(x);
	fun("Hello World");
	fun(21);
	fun(21.6);
	fun('A');
}
