#include <iostream>
#include <fstream>
using namespace std;

class Demo{
  public:
    int roll_num;
    string name;
    Demo() = default;
    Demo(int& roll_num,string& name):roll_num(roll_num), name(name){}
    void Print(){
      cout << roll_num <<" "<< name << endl;
    }
};

int main(){
  Demo d;
  read( cin, &d);
}

