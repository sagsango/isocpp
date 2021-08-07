#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A{
	public:
		template< typename T>
			T add(T a, T b){
				cout << "ADD:0" << endl;
				return a + b;
			}
		A(){}
		~A(){}
};

template<>
int A::add<int>(int a,int b){
	cout << "ADD:1" << endl;
	return a + b;
}


template<>
float A::add<float>(float a,float b){
	cout << "ADD:2" << endl;
	return a + b;
}

int main(){
	A a;
	cout << a.add(10,10) << endl;
	cout << a.add<int>(10,10) << endl;
	cout << a.add<float>(10.0,10.0) << endl;
	cout << a.add<string>("Hello"," World!") << endl;
}

