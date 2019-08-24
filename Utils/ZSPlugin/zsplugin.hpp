#ifndef __ZSS_PLUGIN_H__
#define __ZSS_PLUGIN_H__
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <map>
#include <shared_mutex>
#include <mutex>
#include <cstring>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(long count = 0)
        : count_(count) {
    }
    Semaphore(const Semaphore& s):count_(0){
    }

    void signal(unsigned int c = 1) {
        std::unique_lock<std::mutex> lock(mutex_);
        count_=c;
        cv_.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [=] { return count_ > 0; });
        --count_;
    }

    bool try_wait(){
        std::unique_lock<std::mutex> lock(mutex_);
        if(count_ > 0){
            --count_;
            return true;
        }
        return false;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    long count_;
};
class ZSData{
public:
    ZSData():_size(0),_capacity(0),_data(nullptr){}
    ZSData(const ZSData& data):_size(0),_capacity(0),_data(nullptr){
        store(data);
    }
    ~ZSData(){
        if(_capacity > 0){
            free(_data);
        }
    }
    // thread-safe
    virtual int size() const {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _size;
    }
    virtual const void* data() const { return _data; }
    virtual void store(const ZSData& data){
        store(data.data(),data._size);
    }
    virtual void store(const void* const data,unsigned long size){
        std::unique_lock<std::shared_mutex> lock(_mutex);
        resize(size);
        memcpy(_data,data,size);
    }
    // thread-unsafe
    virtual void resize(const unsigned long size){
        if(size > _capacity){
            if(_data != nullptr){
                free(_data);
            }
            _data = malloc(size);
            _capacity = size;
        }
        _size = size;
    }
    virtual void* ptr() {
        return _data;
    }
protected:
    unsigned long _size;
    int _capacity;
    void* _data;
    mutable std::shared_mutex _mutex;
};
class ZSSemaData:public ZSData,public Semaphore{};
class ZSPlugin{
public:
    ZSPlugin(){}
    virtual ~ZSPlugin(){}
    virtual void run()=0;
    virtual void publish(const std::string&& msg,const void* data = nullptr,const unsigned long size = 0) final{
        auto it = _subscribers.find(msg);
        if (it != _subscribers.end()){
            for(auto p:_subscribers[msg]){
                p->store(msg,data,size);
            }
        }
    }
    virtual void publish(const std::string&& msg,const ZSData& data) final{
        auto it = _subscribers.find(msg);
        if (it != _subscribers.end()){
            for(auto p:_subscribers[msg]){
                p->store(msg,data);
            }
        }
    }
    virtual void receive(const std::string& msg){
        auto it = _databox.find(msg);
        if (it == _databox.end()){
            std::cerr << "ERROR : didn't DECLARE to RECEIVE this kind of message, check your message type : " << msg << std::endl;
            return;
        }
        it->second.wait();
    }
    virtual void receive(const std::string& msg,ZSData& data) final{
        auto it = _databox.find(msg);
        if (it == _databox.end()){
            std::cerr << "ERROR : didn't DECLARE to RECEIVE this kind of message, check your message type : " << msg << std::endl;
            return;
        }
        it->second.wait();
        data.store(it->second);
    }
    virtual bool try_receive(const std::string& msg,ZSData& data) final{
        auto it = _databox.find(msg);
        if (it == _databox.end()){
            std::cerr << "ERROR : didn't DECLARE to RECEIVE this kind of message, check your message type : " << msg << std::endl;
            return false;
        }
        bool res = it->second.try_wait();
        if(res){
            data.store(it->second);
        }
        return res;
    }
    virtual void link(ZSPlugin* p,const std::string& msg) final{
        auto it = _subscribers.find(msg);
        if (it == _subscribers.end()){
            std::cerr << "ERROR : didn't DECLARE to PUBLISH message : " << msg << std::endl;
            return;
        }
        it->second.push_back(p);
    }
    virtual void store(const std::string& msg,const void* data = nullptr,const unsigned long size = 0) final{
        auto it = _databox.find(msg);
        if (it == _databox.end()){
            std::cerr << "ERROR : didn't DECLARE to STORE this kind of message, check your message type : " << msg << std::endl;
            return;
        }
        if(data != nullptr && size > 0)
            it->second.store(data,size);
        it->second.signal();
    }
    virtual void store(const std::string& msg,const ZSData& data) final{
        auto it = _databox.find(msg);
        if (it == _databox.end()){
            std::cerr << "ERROR : didn't DECLARE to STORE this kind of message, check your message type : " << msg << std::endl;
            return;
        }
        it->second.store(data);
        it->second.signal();
    }
    virtual void declare_receive(const std::string& msg) final{
        auto it = _databox.find(msg);
        if (it != _databox.end()){
            std::cerr << "ERROR : REDECLARE, check your message type : " << msg << std::endl;
            return;
        }
        _databox.insert(std::pair<std::string,ZSSemaData>(msg,ZSSemaData()));
    }
    virtual void declare_publish(const std::string& msg) final{
        auto it = _subscribers.find(msg);
        if (it != _subscribers.end()){
            std::cerr << "ERROR : REDECLARE_PUBLISH, check your message type : " << msg << std::endl;
            return;
        }
        _subscribers[msg] = {};
    }
private:
    std::map<std::string,std::list<ZSPlugin*>> _subscribers = {};
    std::map<std::string,class ZSSemaData> _databox = {};
};

#endif // __ZSS_PLUGIN_H__
