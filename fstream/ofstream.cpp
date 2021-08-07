
#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::ofstream outfile("out.txt");
    for(int i=0;i<10000000;++i){
        outfile << i <<" ";
        //outfile.flush(); // write data forcefuly from buffer to file when flush is called
    }
    outfile.close();
}
