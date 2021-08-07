#include <iostream>
#include <string>
#include <vector>

using namespace std;

// template function
template< typename type>
type add(type a,type b){
	type c = a + b;
	return c;
}

// template specialization
template<>
char add<char>(char a, char b){
	int c = (a + b) % 256;
	return char(c);
}



int main(){
	cout << add<int>(10,20) << endl;
	cout << add<float>(10.1,20.2) << endl;
	cout << add<char>('A','a') << endl;
	cout << add<string>("Hello"," World!") << endl;
}

