#include <iostream>
#include <memory>
#include <list>
#include <stack>

using namespace std;


// interface of stack     <stack.h>
class Stack{
	public:
		Stack(){};
		virtual ~Stack(){}; // TODO: think why virtual distructor
		virtual void push(int)=0;
		virtual void pop(void)=0;
		virtual int top(void)=0;
		virtual int size()=0;
};




// arrayStack using stack interface			<arrStack.h>
class arrayStack: public Stack{
	private:
		int max_size, i;
		int *arr;
	public:
		arrayStack(){
			max_size = 1<<10;
			i = 0;
			arr = new int[max_size];
		}
		arrayStack(int max_size):max_size(max_size){
			i = 0;
			arr = new int[max_size];
		}
		~arrayStack(){
			delete [] arr;
		}
		void push(int);
		void pop(void);
		int top(void);
		int size();
};



// listStack using stack interface  <listStack.h>
class listStack: public Stack{
	private:
		std::list<int>m_list;
	public:
		listStack(){};
		~listStack(){
			m_list.clear();
		}
		void push(int);
		void pop(void);
		int top(void);
		int size();
};



// definition of arrayStack member functions		<arrStack.cpp>
void arrayStack::push(int x){
	arr[i++] = x;
}

void arrayStack::pop(void){
	--i;
}

int arrayStack::top(void){
	return arr[--i];
}

int arrayStack::size(){
	return i;
}



// definition of listStack member function	<listStack.cpp>
void listStack::push(int x){
	m_list.push_back(x);
}

void listStack::pop(void){
	m_list.pop_back();
}

int listStack::top(){
	return m_list.back();
}

int listStack::size(){
	return m_list.size();
}


// declaration of function f 		<module1.h>
void f(Stack &); 

// passing to a function using base object type		<module1.cpp>
void f(Stack & st){
    for(int i=0;i<10;++i){
        st.push(10);
    }
    for(int i=0;i<10;++i){
        st.pop();
    }
}


// declaration of function g 		<module2.h>
void g(Stack *);

// passing to a function using base pointer type		<moduble2.cpp>
void g(Stack * ptr){
	for(int i=0;i<10;++i){
		ptr->push(i);
	}
	for(int i=0;i<10;++i){
		ptr->pop();
	}
}



// main function		<main.cpp>
int main(){
	arrayStack as;
  listStack ls;

  f(as);
  f(ls);

	arrayStack *ptr_as = new arrayStack();
	listStack *ptr_ls = new listStack();

	g(ptr_as);
	g(ptr_ls);

	delete ptr_as;
	delete ptr_ls;
	
	return 0;
}
