#include <iostream>
#include <chrono>
#include <thread>
/*
*/
void is_customer(short &count){
    while( count< 15){
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 1000 });
        std::cout << "c> " << ++count << std::endl;
    }
}

void is_operator(short &count){
    while (count) {
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 2000 });
        std::cout << "o< " << --count << std::endl;
    }
}

int main( int argc, char** argv){
    std::cout << "Hello!" << std::endl;
    short count{ 0};
    std::thread t1([ &count](){ is_customer(count);});
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 1000 });
    std::thread t2([ &count](){ is_operator(count);});
    t1.join();
    t2.join();
    return 0;
}
