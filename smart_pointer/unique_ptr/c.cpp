#include <iostream>
#include <memory>
using namespace std;
void fun(char * arr ){
	cout << "fun:" << arr << endl;
	for(int i=0;i<10;++i){
		arr[i] = 'B';
	}
}

int main(){
	unique_ptr< char[] > str;
	//cout << str.get() << endl;
	{
		str = make_unique< char[] >(10);
		for(int i=0;i<10;++i){
			str[i] = 'a';
		}
		cout << "Before:" << str.get() << endl;
		fun(str.get());
		cout << "After:" << str.get() << endl;
		for(int i=0;i<10;++i){
			cout << str[i] <<" ";
		}
		cout << endl;
	}
	cout <<"JJ"<< str.get() << endl;

}
