


#include <iostream>
using namespace std;


// TODO: all the objects of hello share same static var
class hello{
	public:
		void fun(){
			static int done = 0;
			if( !done ){
				cout << "Hello and Done" << endl;
				done = 1;
			}else{
				cout << "Done" << endl;
			}
		}
};

int main(){
	hello h;
	h.fun();
	h.fun();

	hello x;
	x.fun();
	x.fun();
}
