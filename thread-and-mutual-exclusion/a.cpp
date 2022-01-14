#include <iostream>
#include <thread>

std::thread t[2];

void function(){
	for(int i=0;i<100;++i){
		std::cout << i << std::endl;
		std::fflush(stdout);
	}
}

int main(){
	for(int i=0;i<2;++i){
		t[i] = std::thread(function);
	}
	for(int i=0;i<2;++i){
		t[i].join();
	}
}


