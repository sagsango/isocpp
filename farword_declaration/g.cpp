#include <iostream>
using namespace std;

enum Color{ RED, GREEN };
class A{
	public:
		void msg(Color c){
			cout << ( c == RED ? "RED" : "GREEN" ) << endl;
		}
};


class B{
	private:
		enum Color{ RED, GREEN};
		class A obA;
	public:
		void Hello(){
			obA.msg(RED);
			obA.msg(:REEN);
		}
};

int main(){
	cout << "Hello" << endl;
	class B obB;
	obB.Hello();
}


