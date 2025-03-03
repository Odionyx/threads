#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
/*
*/
class Data{
public:
    mutex mtx;
    int getValue(){return this->value;}
    Data & operator=(const Data& other){
        if (this != &other) this->value= other.value;
        return *this;
    }
    Data(int i): value(i){};
    Data()= default;
    ~Data()= default;
private:
    int value= 0;
};

void swap(Data& d, Data& d2){
    lock(d.mtx, d2.mtx);
    lock_guard<mutex> lk1(d.mtx, adopt_lock);
    lock_guard<mutex> lk2(d2.mtx, adopt_lock);
    Data temp;
    temp= d;
    d= d2;
    d2= temp;
}

void swap2(Data& d, Data& d2){
    scoped_lock(d.mtx, d2.mtx); //C++17
    Data temp;
    temp= d;
    d= d2;
    d2= temp;
}

void swap3(Data& d, Data& d2){
    std::unique_lock<std::mutex> lk1(d.mtx, defer_lock);
    std::unique_lock<std::mutex> lk2(d2.mtx, defer_lock);
    std::lock(lk1, lk2);
    Data temp;
    temp= d;
    d= d2;
    d2= temp;
}
///////////////////////////////////
int main( int  argc, char** argv){
//    cout<< "Hello World!"<< endl;
//    cout<< "main id: "<< this_thread::get_id()<< endl;
    Data d( 9), d2( 2);

    thread t([&](){ swap( d, d2);});
    cout<< "swap  d= "<< d.getValue()<< " , d2= "<< d2.getValue()<< endl;
    t.join();

    thread t2([&](){ swap2( d, d2);});
    cout<< "swap2 d= "<< d.getValue()<< " , d2= "<< d2.getValue()<< endl;
    t2.join();

    thread t3([&](){ swap3( d, d2);});
    cout<< "swap3 d= "<< d.getValue()<< " , d2= "<< d2.getValue()<< endl;
    t3.join();

    return 0;
}
