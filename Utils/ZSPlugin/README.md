# ZSPluginFramework
plugin framework like ROS with publisher and subscriber

# Demo
* Plugin A

```c++
#include "zsplugin.hpp"
class A:public ZSPlugin{
public:
    void run(){
        int count = 0;
        while(true){
            auto&& str = std::to_string(count++);
            publish("string",str.c_str(),str.size());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};
```
* Plugin B
```c++
class B:public ZSPlugin{
public:
    B(){
        declare("string");
    }
    void run(){
        std::string str;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ZSData data;
        while(true){
            receive("string",data);
            std::cout << std::string((const char *)data.data(),data.size());
        }
    }
};
```
* Connect & Run with 10000 B receiver and one A sender.
```c++
int main(){
    const int size = 10000;
    A a;
    B b[size];
    for(int i=0;i<size;i++){
        a.connect(&(b[i]),"string");
    }
    std::thread ta([&]{ a.run();});
    std::thread tb[size];//([&]{ b1.run();});
    for(int i=0;i<size;i++){
        tb[i] = std::thread([&,i]{ b[i].run();});
        SetThreadName(&tb[i],std::string(std::string("plugin_b")+std::to_string(i)).c_str());
    }
    SetThreadName(&ta,"plugin_a");
    ta.join();
}
```

# 19.03.2019
* add try_receive() for async receive messages. (return whether there's a new message with none block)
