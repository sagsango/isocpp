#include <stdio.h>
#include <unistd.h>


#define MAX_LEN 256
static char buf[MAX_LEN];

int main(){
  gethostname(buf, MAX_LEN);
  printf("hostname:%s\n",buf);
  return 0;
}
