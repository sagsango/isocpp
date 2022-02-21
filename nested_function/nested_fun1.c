#include <stdio.h>

int fun1(int x){

	int fun2(int);

	int fun2(int x){
		return x + 1;
	}

	return fun2(x)+1;
}

int main(){
	int x = 10;
	printf("%d\n",fun1(x));
}
