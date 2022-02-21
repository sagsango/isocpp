#include <stdio.h>

void fun1(int x){
	printf("fun1:%d\n",x);
}

int fun2(int x){
	printf("fun2:%d\n",x);
	return 0;
}

int main(){
	void (*ptr1)(int) = &fun1;
	int (*ptr2)(int) = &fun2;

	int x = 10;
	(*ptr1)(x);
	(*ptr2)(x);
}
