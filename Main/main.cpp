#include <iostream>
#include <thread>
#include "dllexport.h"

using namespace std;
int main(){
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
	return 0;
}
