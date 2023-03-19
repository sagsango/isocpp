#include <stdio.h>



//Method as member.{
static int fun(int x, char msg[]){
  for(int i=0;i<x;++i){
    printf("%s:%d\n",msg, i);
  }
  return 0;
}

struct box{
  int (*methodPtr)(int,char[]);
  char msg[20];
};

static struct box BigBox = {
  .methodPtr = fun,
  .msg = "Hello From BigBox"
};
//}Method as member.



//struct array init.{
struct box1{
  int i_mem;
};

struct box1 box1_arr[3] = { [0] = {.i_mem = 0},
                            [1] = {.i_mem = 10},
                            [2] = {.i_mem = -5} 
};
 //}struct array init. 



// int array init.{

static const int i_arr[3] = { [1] = 0,
                              [2] = 1,
                              [0] = 2 
};

// }int array init.



int main(){
  BigBox.methodPtr(5,BigBox.msg);
}
  

