#include <iostream>
using namespace std;

class A;
class B;
enum Color:int;

class B{
	private:
		struct Type{
			Color type;
		};
		A *obA;
	public:
		void Hello();
};

class A{
	public:
		void msg(Color c);
};

enum Color:int{ RED, GREEN };

void A::msg(Color c){
	cout << ( c == RED ? "RED" : "GREEN" ) << endl;
}

void B::Hello(){
	Type t;
	t.type = RED;
	obA = new A();
	obA->msg(RED);
	obA->msg(GREEN);
	obA->msg((Color)(0));
}

int main(){
	cout << "Hello" << endl;
	class B obB;
	obB.Hello();
}



