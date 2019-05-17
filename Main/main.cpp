#include <iostream>
#include <thread>
#include "dllexport.h"
#include <Environment/environment.h>
using namespace std;
int main(){
    Environment env(10666);
    env.step(nullptr,0);
	return 0;
}
