#include "lfsr.hh"
#include<iostream>
#include<chrono>
int main(){
    int init = 1;
    
    int len = 20;
    for(int ii=0;ii<25;ii++){
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> out = lfsr(init,len,0x15);
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << len << " it took " << (stop - start).count() << std::endl;
        len *= 2;
    }
}
