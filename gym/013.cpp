



#include <iostream>
using namespace std;


// TODO: all the objects of hello share same static var
class hello{
	private:
		static int done;
	public:
		void fun(){
			if( !done ){
				cout << "Hello and Done" << endl;
				done = 1;
			}else{
				cout << "Done" << endl;
			}
		}
};

int hello:: done = 0;
int main(){
	hello h;
	h.fun();
	h.fun();

	hello x;
	x.fun();
	x.fun();
}
